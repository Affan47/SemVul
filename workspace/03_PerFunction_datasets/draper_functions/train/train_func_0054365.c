dhcp_control_destroy (omapi_object_t *h,
				   const char *file, int line)
{
	if (h -> type != dhcp_type_control)
		return DHCP_R_INVALIDARG;


	return ISC_R_NOPERM;
}
