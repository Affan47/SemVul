start_drv_threads(struct _adapter *padapter)
{
	padapter->cmdThread = kthread_run(r8712_cmd_thread, padapter, "%s",
			      padapter->pnetdev->name);
	if (IS_ERR(padapter->cmdThread))
		return _FAIL;
	return _SUCCESS;
}
