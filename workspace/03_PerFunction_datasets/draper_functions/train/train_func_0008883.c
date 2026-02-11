free_vrrp(void *data)
{
	vrrp_t *vrrp = data;
	element e;

	FREE(vrrp->iname);
	FREE_PTR(vrrp->send_buffer);
	FREE_PTR(vrrp->lvs_syncd_if);
	FREE_PTR(vrrp->script_backup);
	FREE_PTR(vrrp->script_master);
	FREE_PTR(vrrp->script_fault);
	FREE_PTR(vrrp->script_stop);
	FREE_PTR(vrrp->script);
	FREE(vrrp->ipsecah_counter);

	if (!LIST_ISEMPTY(vrrp->track_ifp))
		for (e = LIST_HEAD(vrrp->track_ifp); e; ELEMENT_NEXT(e))
			FREE(ELEMENT_DATA(e));
	free_list(vrrp->track_ifp);

	if (!LIST_ISEMPTY(vrrp->track_script))
		for (e = LIST_HEAD(vrrp->track_script); e; ELEMENT_NEXT(e))
			FREE(ELEMENT_DATA(e));
	free_list(vrrp->track_script);

	free_list(vrrp->unicast_peer);
	free_list(vrrp->vip);
	free_list(vrrp->evip);
	free_list(vrrp->vroutes);
	FREE(vrrp);
}
