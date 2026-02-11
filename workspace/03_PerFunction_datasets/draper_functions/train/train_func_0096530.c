krb5_verify(const struct passwd *login_info,
	    const struct passwd *su_info,
	    const char *instance)
{
    krb5_error_code ret;
    krb5_principal p;
    krb5_realm *realms, *r;
    char *login_name = NULL;
    int user_ok = 0;

#if defined(HAVE_GETLOGIN) && !defined(POSIX_GETLOGIN)
    login_name = getlogin();
#endif
    ret = krb5_init_context (&context);
    if (ret) {
#if 0
	warnx("krb5_init_context failed: %d", ret);
#endif
	return 1;
    }

    ret = krb5_get_default_realms(context, &realms);
    if (ret)
	return 1;


    for (r = realms; *r != NULL && !user_ok; r++) {

	if (login_name == NULL || strcmp (login_name, "root") == 0)
	    login_name = login_info->pw_name;
	if (strcmp (su_info->pw_name, "root") == 0)
	    ret = krb5_make_principal(context, &p, *r,
				      login_name,
				      instance,
				      NULL);
	else
	    ret = krb5_make_principal(context, &p, *r,
				      su_info->pw_name,
				      NULL);
	if (ret) {
	    krb5_free_host_realm(context, realms);
	    return 1;
	}


	if (su_info->pw_uid == 0 && !krb5_kuserok(context, p, su_info->pw_name))
	    continue;

	ret = krb5_cc_new_unique(context, krb5_cc_type_memory, NULL, &ccache);
	if(ret) {
	    krb5_free_host_realm(context, realms);
	    krb5_free_principal (context, p);
	    return 1;
	}
  	ret = krb5_verify_user(context, p, ccache, NULL, TRUE, NULL);
	krb5_free_principal (context, p);
	switch (ret) {
	case 0:
	    user_ok = 1;
	    break;
	case KRB5_LIBOS_PWDINTR :
	    krb5_cc_destroy(context, ccache);
	    break;
	case KRB5KRB_AP_ERR_BAD_INTEGRITY:
	case KRB5KRB_AP_ERR_MODIFIED:
	    krb5_cc_destroy(context, ccache);
	    krb5_warnx(context, "Password incorrect");
	    break;
	default :
	    krb5_cc_destroy(context, ccache);
	    krb5_warn(context, ret, "krb5_verify_user");
	    break;
	}
    }
    krb5_free_host_realm(context, realms);
    if (!user_ok)
	return 1;
    return 0;
}
