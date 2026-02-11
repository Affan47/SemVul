append_host_string(krb5_context context, struct krb5_krbhst_data *kd,
		   const char *host, int def_port, int port)
{
    struct krb5_krbhst_info *hi;

    hi = parse_hostspec(context, kd, host, def_port, port);
    if(hi == NULL)
	return krb5_enomem(context);

    append_host_hostinfo(kd, hi);
    return 0;
}
