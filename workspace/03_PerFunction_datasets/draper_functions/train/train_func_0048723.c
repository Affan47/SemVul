__pkey_manage_ask_external_file_password (const gchar *cert_dn)
{
	gchar *password;
	gchar *aux = NULL;


	printf (_("The file that holds private key for certificate\n'%s' is password-protected.\n\n"), cert_dn);

	aux = getpass ("Please, insert the password corresponding to this file:");

	if (!aux || aux[0] == '\0') {
		return NULL;
	} else {
		password = g_strdup (aux);
		memset (aux, 0, strlen(aux));
	}

	return password;
}
