kerberos5_auth(socket, canonical)

int socket;
const char *canonical;
{
    krb5_error_code retval;
    krb5_context context;
    krb5_ccache ccdef;
    krb5_principal client = NULL, server = NULL;
    krb5_error *err_ret = NULL;

    krb5_auth_context auth_context = NULL;

    krb5_init_context(&context);
    krb5_auth_con_init(context, &auth_context);

    if ((retval = krb5_cc_default(context, &ccdef))) {
        report(stderr, "krb5_cc_default: %s\n", error_message(retval));
        return(PS_ERROR);
    }

    if ((retval = krb5_cc_get_principal(context, ccdef, &client))) {
        report(stderr, "krb5_cc_get_principal: %s\n", error_message(retval));
        return(PS_ERROR);
    }

    if ((retval = krb5_sname_to_principal(context, canonical, "pop",
           KRB5_NT_UNKNOWN,
           &server))) {
        report(stderr, "krb5_sname_to_principal: %s\n", error_message(retval));
        return(PS_ERROR);
    }

    retval = krb5_sendauth(context, &auth_context, (krb5_pointer) &socket,
         "KPOPV1.0", client, server,
         AP_OPTS_MUTUAL_REQUIRED,
         NULL,
         0,
         ccdef,
         &err_ret, 0,

         NULL);

    krb5_free_principal(context, server);
    krb5_free_principal(context, client);
    krb5_auth_con_free(context, auth_context);

    if (retval) {
#ifdef HEIMDAL
      if (err_ret && err_ret->e_text) {
	  char *t = err_ret->e_text;
	  char *tt = sdump(t, strlen(t));
          report(stderr, GT_("krb5_sendauth: %s [server says '%s']\n"),
                 error_message(retval), tt);
	  free(tt);
#else
      if (err_ret && err_ret->text.length) {
	  char *tt = sdump(err_ret->text.data, err_ret->text.length);
          report(stderr, GT_("krb5_sendauth: %s [server says '%s']\n"),
		 error_message(retval), tt);
	  free(tt);
#endif
	  krb5_free_error(context, err_ret);
      } else
          report(stderr, "krb5_sendauth: %s\n", error_message(retval));
      return(PS_ERROR);
    }

    return 0;
}
