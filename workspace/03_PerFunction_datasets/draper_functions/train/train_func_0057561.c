vmci_host_do_queuepair_setpf(struct vmci_host_dev *vmci_host_dev,
					const char *ioctl_name,
					void __user *uptr)
{
	struct vmci_qp_page_file_info page_file_info;
	struct vmci_qp_page_file_info __user *info = uptr;
	s32 result;

	if (vmci_host_dev->user_version < VMCI_VERSION_HOSTQP ||
	    vmci_host_dev->user_version >= VMCI_VERSION_NOVMVM) {
		vmci_ioctl_err("not supported on this VMX (version=%d)\n",
			       vmci_host_dev->user_version);
		return -EINVAL;
	}

	if (vmci_host_dev->ct_type != VMCIOBJ_CONTEXT) {
		vmci_ioctl_err("only valid for contexts\n");
		return -EINVAL;
	}

	if (copy_from_user(&page_file_info, uptr, sizeof(*info)))
		return -EFAULT;


	if (put_user(VMCI_SUCCESS, &info->result)) {


		return -EFAULT;
	}

	result = vmci_qp_broker_set_page_store(page_file_info.handle,
						page_file_info.produce_va,
						page_file_info.consume_va,
						vmci_host_dev->context);
	if (result < VMCI_SUCCESS) {
		if (put_user(result, &info->result)) {


			return -EFAULT;
		}
	}

	return 0;
}
