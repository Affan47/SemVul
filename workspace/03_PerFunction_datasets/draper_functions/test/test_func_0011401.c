vrrp_native_ipv6_handler(vector_t *strvec)
{
	vrrp_rt *vrrp = LIST_TAIL_DATA(vrrp_data->vrrp);
	vrrp->family = AF_INET6;

	if (vrrp->auth_type != VRRP_AUTH_NONE)
		vrrp->auth_type = VRRP_AUTH_NONE;
}
