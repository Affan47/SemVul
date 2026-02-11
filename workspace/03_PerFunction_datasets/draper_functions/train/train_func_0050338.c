__genwqe_execute_raw_ddcb(struct genwqe_dev *cd,
			      struct genwqe_ddcb_cmd *cmd,
			      unsigned int f_flags)
{
	int rc = 0;
	struct pci_dev *pci_dev = cd->pci_dev;
	struct ddcb_requ *req = container_of(cmd, struct ddcb_requ, cmd);

	if (cmd->asiv_length > DDCB_ASIV_LENGTH) {
		dev_err(&pci_dev->dev, "[%s] err: wrong asiv_length of %d\n",
			__func__, cmd->asiv_length);
		return -EINVAL;
	}
	if (cmd->asv_length > DDCB_ASV_LENGTH) {
		dev_err(&pci_dev->dev, "[%s] err: wrong asv_length of %d\n",
			__func__, cmd->asiv_length);
		return -EINVAL;
	}
	rc = __genwqe_enqueue_ddcb(cd, req, f_flags);
	if (rc != 0)
		return rc;

	rc = __genwqe_wait_ddcb(cd, req);
	if (rc < 0)
		goto err_exit;

	if (ddcb_requ_collect_debug_data(req)) {
		if (copy_to_user((struct genwqe_debug_data __user *)
				 (unsigned long)cmd->ddata_addr,
				 &req->debug_data,
				 sizeof(struct genwqe_debug_data)))
			return -EFAULT;
	}


	if (cmd->retc != DDCB_RETC_COMPLETE) {


		rc = -EBADMSG;
	}

	return rc;

 err_exit:
	__genwqe_purge_ddcb(cd, req);

	if (ddcb_requ_collect_debug_data(req)) {
		if (copy_to_user((struct genwqe_debug_data __user *)
				 (unsigned long)cmd->ddata_addr,
				 &req->debug_data,
				 sizeof(struct genwqe_debug_data)))
			return -EFAULT;
	}
	return rc;
}
