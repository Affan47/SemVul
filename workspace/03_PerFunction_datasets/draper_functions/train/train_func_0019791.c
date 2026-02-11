dhcp_failover_listener_destroy (omapi_object_t *h,
					      const char *file, int line)
{
	dhcp_failover_listener_t *l;

	if (h -> type != dhcp_type_failover_listener)
		return DHCP_R_INVALIDARG;
	l = (dhcp_failover_listener_t *)h;
	if (l -> next)
		dhcp_failover_listener_dereference (&l -> next, file, line);

	return ISC_R_SUCCESS;
}
