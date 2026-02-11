ldapctl_set_bind_password(
	LdapControl* ctl, const gchar *value, gboolean encrypt, gboolean change ) {
	gchar *buf, *tmp;

	ctl->bindPass = mgu_replace_string( ctl->bindPass, value );

	if ( ctl->bindPass == NULL )
		return;

	g_strstrip( ctl->bindPass );

	buf = tmp = NULL;
	if ( encrypt ) {

		if (ctl->bindPass[0] == '!' || change) {
			if (ctl->bindPass[0] != '!' && change)
				buf = mgu_replace_string( buf, ctl->bindPass );
			else {
				if (ctl->bindPass[1] != '|')
					buf = mgu_replace_string( buf, ctl->bindPass + 1 );
				else {

					buf = mgu_replace_string( buf, ctl->bindPass + 2 );
					qp_decode_line(buf);
				}
			}

			passcrypt_encrypt( buf, strlen(buf) );
			if (ctl->bindPass[0] != '!' && change) {

				tmp = g_malloc0(qp_get_q_encoding_len(buf) + 1);
				qp_q_encode(tmp, buf);
				g_free(buf);
				buf = g_strconcat( "!|", tmp, NULL );
				g_free(tmp);
			}

			ctl->bindPass = mgu_replace_string( ctl->bindPass, buf );
			g_free(buf);

		}
	}
	debug_print("setting bindPassword\n");
}
