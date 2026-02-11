ehci_mem_cleanup(struct oxu_hcd *oxu)
{
	kfree(oxu->murb_pool);
	oxu->murb_pool = NULL;

	if (oxu->async)
		qh_put(oxu->async);
	oxu->async = NULL;

	del_timer(&oxu->urb_timer);

	oxu->periodic = NULL;


	kfree(oxu->pshadow);
	oxu->pshadow = NULL;
}
