config_log(struct configuration *p, int **colsp, int *numcolsp)
{
	int ml;
	int *cols;
	int numcols;
	const char *t;

	ml = 0;
	cols = *colsp;
	numcols = *numcolsp;
	if ((t = gettoken(p)) != t_open)
		return t;
	while ((t = gettoken(p)) != t_close) {
		if (t != t_string)
			return t;
		if (!strcasecmp(p->tokbuf, c_ctime))
			ml = ML_CTIME;
		else if (!strcasecmp(p->tokbuf, c_remote_user))
			ml = ML_USERNAME;
		else if (!strcasecmp(p->tokbuf, c_remote_address))
			ml = ML_REMOTE_ADDRESS;
		else if (!strcasecmp(p->tokbuf, c_remote_port))
			ml = ML_REMOTE_PORT;
		else if (!strcasecmp(p->tokbuf, c_local_address))
			ml = ML_LOCAL_ADDRESS;
		else if (!strcasecmp(p->tokbuf, c_local_port))
			ml = ML_LOCAL_PORT;
		else if (!strcasecmp(p->tokbuf, c_server_name))
			ml = ML_SERVERNAME;
		else if (!strcasecmp(p->tokbuf, c_method))
			ml = ML_METHOD;
		else if (!strcasecmp(p->tokbuf, c_uri))
			ml = ML_URI;
		else if (!strcasecmp(p->tokbuf, c_version))
			ml = ML_VERSION;
		else if (!strcasecmp(p->tokbuf, c_status))
			ml = ML_STATUS;
		else if (!strcasecmp(p->tokbuf, c_content_length))
			ml = ML_CONTENT_LENGTH;
		else if (!strcasecmp(p->tokbuf, c_referer))
			ml = ML_REFERER;
		else if (!strcasecmp(p->tokbuf, c_user_agent))
			ml = ML_USER_AGENT;
		else if (!strcasecmp(p->tokbuf, c_bytes_read))
			ml = ML_BYTES_READ;
		else if (!strcasecmp(p->tokbuf, c_bytes_written))
			ml = ML_BYTES_WRITTEN;
		else if (!strcasecmp(p->tokbuf, c_query_string))
			ml = ML_QUERY_STRING;
		else if (!strcasecmp(p->tokbuf, c_time_taken))
			ml = ML_TIME_TAKEN;
		else if (!strcasecmp(p->tokbuf, c_micro_time))
			ml = ML_MICRO_TIME;
		else if (!strcasecmp(p->tokbuf, c_pid))
			ml = ML_PID;
		else
			return e_keyword;
		++numcols;
		cols = realloc(cols, sizeof *cols * numcols);
		if (cols == 0)
			return e_memory;
		cols[numcols - 1] = ml;
		*colsp = cols;
		*numcolsp = numcols;
	}
	return 0;
}
