parse_tty(const lnode *n, search_items *s)
{
	char *str, *ptr, *term=n->message;


	if (event_pid != -1) {
		str = strstr(n->message, "pid=");
		if (str) {
			ptr = str + 4;
			term = strchr(ptr, ' ');
			if (term == NULL)
				return 1;
			*term = 0;
			errno = 0;
			s->pid = strtoul(ptr, NULL, 10);
			if (errno)
				return 2;
			*term = ' ';
		}
	}


	str = strstr(term, " uid=");
	if (str) {
		ptr = str + 4;
		term = strchr(ptr, ' ');
		if (term == NULL)
			return 3;
		*term = 0;
		errno = 0;
		s->uid = strtoul(ptr, NULL, 10);
		if (errno)
			return 4;
		*term = ' ';
	}


	str = strstr(term, "auid=");
	if (str == NULL)
		return 5;
	ptr = str + 5;
	term = strchr(ptr, ' ');
	if (term)
		*term = 0;
	errno = 0;
	s->loginuid = strtoul(ptr, NULL, 10);
	if (errno)
		return 6;
	if (term)
		*term = ' ';
	else
		term = ptr;


	if (event_session_id != -2 ) {
		str = strstr(term, "ses=");
		if (str) {
			ptr = str + 4;
			term = strchr(ptr, ' ');
			if (term == NULL)
				return 7;
			*term = 0;
			errno = 0;
			s->session_id = strtoul(ptr, NULL, 10);
			if (errno)
				return 8;
			*term = ' ';
		}
	}


	if (event_comm) {

		str = strstr(term, "comm=");
		if (str) {
			str += 5;
			if (*str == '"') {
				str++;
				term = strchr(str, '"');
				if (term == NULL)
					return 11;
				*term = 0;
				s->comm = strdup(str);
				*term = '"';
			} else
				s->comm = unescape(str);
		}
	}

	return 0;
}
