get_req_for_dnsexit_server(DYN_DNS_CLIENT *p_self, int infcnt, int alcnt)
{
	if (p_self == NULL)
	{

		return 0;
	}

	return sprintf(p_self->p_req_buffer, DNSEXIT_UPDATE_IP_HTTP_REQUEST,
		       p_self->info[infcnt].dyndns_server_url,
		       p_self->info[infcnt].credentials.my_username,
		       p_self->info[infcnt].credentials.my_password,
		       p_self->info[infcnt].alias_info[alcnt].names.name,
		       p_self->info[infcnt].my_ip_address.name,
		       p_self->info[infcnt].dyndns_server_name.name);
}
