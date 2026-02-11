add_server_conf(struct server_conf *server_p)
{
	if(EmptyString(server_p->class_name))
		server_p->class = default_class;
	else
		server_p->class = find_class(server_p->class_name);

	if(server_p->class == default_class)
	{
		conf_report_error("Warning connect::class invalid for %s", server_p->name);

		rb_free(server_p->class_name);
		server_p->class_name = rb_strdup("default");
	}

	if(strpbrk(server_p->host, "?*") != NULL)
		return;

	if(rb_inet_pton_sock(server_p->host, (struct sockaddr *)&server_p->ipnum) > 0)
		return;

	server_p->dns_query =
		lookup_hostname(server_p->host, GET_SS_FAMILY(&server_p->ipnum), conf_dns_callback,
				server_p);
}
