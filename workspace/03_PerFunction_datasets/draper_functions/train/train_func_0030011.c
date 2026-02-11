do_execute_ddcb(struct genwqe_file *cfile,
			   unsigned long arg, int raw)
{
	int rc;
	struct genwqe_ddcb_cmd *cmd;
	struct ddcb_requ *req;
	struct genwqe_dev *cd = cfile->cd;
	struct file *filp = cfile->filp;

	cmd = ddcb_requ_alloc();
	if (cmd == NULL)
		return -ENOMEM;

	req = container_of(cmd, struct ddcb_requ, cmd);

	if (copy_from_user(cmd, (void __user *)arg, sizeof(*cmd))) {
		ddcb_requ_free(cmd);
		return -EFAULT;
	}

	if (!raw)
		rc = genwqe_execute_ddcb(cfile, cmd);
	else
		rc = __genwqe_execute_raw_ddcb(cd, cmd, filp->f_flags);


	if (copy_to_user((void __user *)arg, cmd,
			 sizeof(*cmd) - DDCB_ASIV_LENGTH)) {
		ddcb_requ_free(cmd);
		return -EFAULT;
	}

	ddcb_requ_free(cmd);
	return rc;
}
