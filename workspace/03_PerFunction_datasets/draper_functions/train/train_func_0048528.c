format_keytype(krb5_key_data *k, krb5_salt *def_salt, char *buf, size_t buf_len)
{
    krb5_error_code ret;
    char *s;
    int aret;

    buf[0] = '\0';
    ret = krb5_enctype_to_string (context,
				  k->key_data_type[0],
				  &s);
    if (ret) {
	aret = asprintf (&s, "unknown(%d)", k->key_data_type[0]);
	if (aret == -1)
	    return;
    }
    strlcpy(buf, s, buf_len);
    free(s);

    strlcat(buf, "(", buf_len);

    ret = krb5_salttype_to_string (context,
				   k->key_data_type[0],
				   k->key_data_type[1],
				   &s);
    if (ret) {
	aret = asprintf (&s, "unknown(%d)", k->key_data_type[1]);
	if (aret == -1)
	    return;
    }
    strlcat(buf, s, buf_len);
    free(s);

    aret = 0;
    if (cmp_salt(def_salt, k) == 0)
	s = strdup("");
    else if(k->key_data_length[1] == 0)
	s = strdup("()");
    else
	aret = asprintf (&s, "(%.*s)", k->key_data_length[1],
			 (char *)k->key_data_contents[1]);
    if (aret == -1 || s == NULL)
	return;
    strlcat(buf, s, buf_len);
    free(s);
    aret = asprintf (&s, "[%d]", k->key_data_kvno);
    if (aret == -1)
	return;
    strlcat(buf, ")", buf_len);

    strlcat(buf, s, buf_len);
    free(s);
}
