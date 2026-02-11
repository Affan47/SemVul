msgfromstream_string(FILE * f)
{
	char		buf[MAXMSGLINE];
	const char *	bufmax = buf + sizeof(buf);
	struct ha_msg*	ret;
	char *		getsret;


	if ((ret = ha_msg_new(0)) == NULL) {


		if (   (!ferror(f) || (errno != EINTR && errno != EAGAIN))
		&&	!feof(f)) {
			cl_log(LOG_ERR, "msgfromstream: cannot get message");
		}
		return(NULL);
	}


	while(1) {
		getsret = fgets(buf, MAXMSGLINE, f);
		if (!getsret) {
			break;
		}

		if (strnlen(buf, MAXMSGLINE) > MAXMSGLINE - 2) {
			cl_log(LOG_DEBUG
			,	"msgfromstream: field too long [%s]"
			,	buf);
		}

		if (!strcmp(buf, MSG_END)) {
			break;
		}


		if (ha_msg_add_nv(ret, buf, bufmax) != HA_OK) {
			cl_log(LOG_ERR, "NV failure (msgfromsteam): [%s]"
			,	buf);
			ha_msg_del(ret); ret=NULL;
			return(NULL);
		}
	}
	return(ret);
}
