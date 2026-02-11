privcmd_ioctl_hypercall(void __user *udata)
{
	struct privcmd_hypercall hypercall;
	long ret;

	if (copy_from_user(&hypercall, udata, sizeof(hypercall)))
		return -EFAULT;

	xen_preemptible_hcall_begin();
	ret = privcmd_call(hypercall.op,
			   hypercall.arg[0], hypercall.arg[1],
			   hypercall.arg[2], hypercall.arg[3],
			   hypercall.arg[4]);
	xen_preemptible_hcall_end();

	return ret;
}
