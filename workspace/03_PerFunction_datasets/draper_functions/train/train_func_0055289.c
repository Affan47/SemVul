rfc1035_spf_compute(char *record,
			 struct rfc1035_spf_info *info)
{
	unsigned n=get_words(record, NULL);
	char **words=malloc((n+1)*sizeof(char *));
	char rc;

	if (words == NULL)
	{
		set_err_msg(info->errmsg_buf, info->errmsg_buf_size,
			    strerror(errno));
		return SPF_ERROR;
	}

	get_words(record, words);
	words[n]=0;

	rc=spf_compute(words, info);
	free(words);
	return rc;
}
