replace_filter(Slapi_Filter	*f, char *s)
{
	Slapi_Filter	*newf = NULL;
	Slapi_Filter	*temp = NULL;


	char *buf = slapi_ch_strdup(s);

	newf = slapi_str2filter(buf);
	slapi_ch_free((void **)&buf);

	if (NULL == newf) {
		return -1;
	}


	temp = f->f_next;
	*f = *newf;
	f->f_next = temp;

	slapi_ch_free((void**)&newf);
	return 0;
}
