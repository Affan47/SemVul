srv_get_hosts(krb5_context context, struct krb5_krbhst_data *kd,
	      const char *proto, const char *service)
{
    krb5_error_code ret;
    krb5_krbhst_info **res;
    int count, i;

    if (krb5_realm_is_lkdc(kd->realm))
	return;

    ret = srv_find_realm(context, &res, &count, kd->realm, "SRV", proto, service,
			 kd->port);
    _krb5_debug(context, 2, "searching DNS for realm %s %s.%s -> %d",
		kd->realm, proto, service, ret);
    if (ret)
	return;
    for(i = 0; i < count; i++)
	append_host_hostinfo(kd, res[i]);
    free(res);
}
