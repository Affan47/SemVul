close_vrrp_socket(vrrp_t * vrrp)
{
	if (LIST_ISEMPTY(vrrp->unicast_peer)) {
		if_leave_vrrp_group(vrrp->family, vrrp->fd_in, vrrp->ifp);
	} else {
		close(vrrp->fd_in);
	}
	close(vrrp->fd_out);
}
