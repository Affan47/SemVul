adcli_conn_set_login_ccache_name (adcli_conn *conn,
                                  const char *ccname)
{
	char *newval = NULL;

	return_if_fail (conn != NULL);

	if (ccname) {
		newval = strdup (ccname);
		return_if_fail (newval != NULL);
	}

	if (conn->login_ccache_name) {
		if (conn->login_ccache_name_is_krb5)
			krb5_free_string (conn->k5, conn->login_ccache_name);
		else
			free (conn->login_ccache_name);
	}

	if (conn->ccache) {
		krb5_cc_close (conn->k5, conn->ccache);
		conn->ccache = NULL;
	}

	conn->login_ccache_name = newval;
	conn->login_ccache_name_is_krb5 = 0;
}
