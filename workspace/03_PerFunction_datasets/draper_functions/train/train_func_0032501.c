omapi_protocol_destroy (omapi_object_t *h,
				     const char *file, int line)
{
	omapi_protocol_object_t *p;
	if (h -> type != omapi_type_protocol)
		return DHCP_R_INVALIDARG;
	p = (omapi_protocol_object_t *)h;
	if (p -> message)
		omapi_message_dereference (&p -> message, file, line);


	if (p -> default_auth && !p -> remote_auth_list)
		dfree (p -> default_auth, file, line);

	while (p -> remote_auth_list) {
		omapi_remote_auth_t *r = p -> remote_auth_list;
		p -> remote_auth_list =  p -> remote_auth_list -> next;
		omapi_object_dereference (&r -> a, file, line);
		dfree (r, file, line);
	}
	return ISC_R_SUCCESS;
}
