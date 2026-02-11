vrrp_log_int_down(vrrp_t *vrrp)
{
	if (!IF_ISUP(vrrp->ifp))
		log_message(LOG_INFO, "Kernel is reporting: interface %s DOWN",
		       IF_NAME(vrrp->ifp));
	if (!LIST_ISEMPTY(vrrp->track_ifp))
		vrrp_log_tracked_down(vrrp->track_ifp);
}
