krb5_get_init_creds_opt_set_addressless(krb5_context context,
					krb5_get_init_creds_opt *opt,
					krb5_boolean addressless)
{
    krb5_error_code ret;
    ret = require_ext_opt(context, opt, "init_creds_opt_set_pac_req");
    if (ret)
	return ret;
    if (addressless)
	opt->opt_private->addressless = KRB5_INIT_CREDS_TRISTATE_TRUE;
    else
	opt->opt_private->addressless = KRB5_INIT_CREDS_TRISTATE_FALSE;
    return 0;
}
