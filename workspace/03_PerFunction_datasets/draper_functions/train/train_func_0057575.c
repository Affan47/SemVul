vmci_host_do_send_datagram(struct vmci_host_dev *vmci_host_dev,
				      const char *ioctl_name,
				      void __user *uptr)
{
	struct vmci_datagram_snd_rcv_info send_info;
	struct vmci_datagram *dg = NULL;
	u32 cid;

	if (vmci_host_dev->ct_type != VMCIOBJ_CONTEXT) {
		vmci_ioctl_err("only valid for contexts\n");
		return -EINVAL;
	}

	if (copy_from_user(&send_info, uptr, sizeof(send_info)))
		return -EFAULT;

	if (send_info.len > VMCI_MAX_DG_SIZE) {
		vmci_ioctl_err("datagram is too big (size=%d)\n",
			       send_info.len);
		return -EINVAL;
	}

	if (send_info.len < sizeof(*dg)) {
		vmci_ioctl_err("datagram is too small (size=%d)\n",
			       send_info.len);
		return -EINVAL;
	}

	dg = kmalloc(send_info.len, GFP_KERNEL);
	if (!dg) {
		vmci_ioctl_err(
			"cannot allocate memory to dispatch datagram\n");
		return -ENOMEM;
	}

	if (copy_from_user(dg, (void __user *)(uintptr_t)send_info.addr,
			   send_info.len)) {
		vmci_ioctl_err("error getting datagram\n");
		kfree(dg);
		return -EFAULT;
	}

	if (VMCI_DG_SIZE(dg) != send_info.len) {
		vmci_ioctl_err("datagram size mismatch\n");
		kfree(dg);
		return -EINVAL;
	}

	pr_devel("Datagram dst (handle=0x%x:0x%x) src (handle=0x%x:0x%x), payload (size=%llu bytes)\n",
		 dg->dst.context, dg->dst.resource,
		 dg->src.context, dg->src.resource,
		 (unsigned long long)dg->payload_size);


	cid = vmci_ctx_get_id(vmci_host_dev->context);
	send_info.result = vmci_datagram_dispatch(cid, dg, true);
	kfree(dg);

	return copy_to_user(uptr, &send_info, sizeof(send_info)) ? -EFAULT : 0;
}
