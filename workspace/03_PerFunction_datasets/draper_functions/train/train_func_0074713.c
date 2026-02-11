chk_min_cfg(vrrp_t * vrrp)
{
	if (vrrp->vrid == 0) {
		log_message(LOG_INFO, "VRRP_Instance(%s) the virtual id must be set!",
		       vrrp->iname);
		return 0;
	}
	if (!vrrp->ifp) {
		log_message(LOG_INFO, "VRRP_Instance(%s) Unknown interface !",
		       vrrp->iname);
		return 0;
	}

	return 1;
}
