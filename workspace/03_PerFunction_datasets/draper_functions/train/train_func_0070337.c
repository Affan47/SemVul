lld_timedout(unsigned long ptr)
{
	uioc_t *kioc	= (uioc_t *)ptr;

	kioc->status 	= -ETIME;
	kioc->timedout	= 1;

	con_log(CL_ANN, (KERN_WARNING "megaraid cmm: ioctl timed out\n"));

	wake_up(&wait_q);
}
