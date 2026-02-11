inotbl_put_ctl_page(int is_aggregate, struct dinomap *ctlpage_ptr)
{
	int ipcp_rc = FSCK_OK;

	if (agg_recptr->processing_readwrite) {

		ujfs_swap_dinomap(ctlpage_ptr);
		ipcp_rc = mapctl_put((void *) ctlpage_ptr);
	}
	return (ipcp_rc);
}
