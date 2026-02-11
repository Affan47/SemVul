forward_subject(ENVELOPE *env, int flags)
{
    size_t l;
    char  *p, buftmp[MAILTMPLEN];

    if(!env)
      return(NULL);

    dprint((9, "checking subject: \"%s\"\n",
	       env->subject ? env->subject : "NULL"));

    if(env->subject && env->subject[0]){
	snprintf(buftmp, sizeof(buftmp), "%s", env->subject);
	buftmp[sizeof(buftmp)-1] = '\0';

	if(rfc1522_decode_to_utf8((unsigned char *) tmp_20k_buf,
				  SIZEOF_20KBUF, buftmp) == (unsigned char *) buftmp)
	  strncpy(tmp_20k_buf, buftmp, SIZEOF_20KBUF);

	tmp_20k_buf[SIZEOF_20KBUF-1] = '\0';

	removing_trailing_white_space(tmp_20k_buf);
	if((l = strlen(tmp_20k_buf)) < 1000 &&
	   (l < 5 || strcmp(tmp_20k_buf+l-5,"(fwd)"))){
	    snprintf(tmp_20k_buf+2000, SIZEOF_20KBUF-2000, "%s (fwd)", tmp_20k_buf);
	    tmp_20k_buf[SIZEOF_20KBUF-2000-1] = '\0';
	    strncpy(tmp_20k_buf, tmp_20k_buf+2000, SIZEOF_20KBUF);
	    tmp_20k_buf[SIZEOF_20KBUF-1] = '\0';
	}


	if(flags & FS_CONVERT_QUOTES)
	  while((p = strchr(tmp_20k_buf, QUOTE)) != NULL)
	    (void)rplstr(p, SIZEOF_20KBUF-(p-tmp_20k_buf), 1, "''");

	return(cpystr(tmp_20k_buf));

    }

    return(cpystr("Forwarded mail...."));
}
