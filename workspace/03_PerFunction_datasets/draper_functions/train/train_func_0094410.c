extract_timestamp(const char *b, event *e)
{
	char *ptr, *tmp, *tnode, *ttype;

	e->node = NULL;
	if (*b == 'n')
		tmp = strndupa(b, 340);
	else
		tmp = strndupa(b, 80);
	ptr = audit_strsplit(tmp);
	if (ptr) {

		if (*ptr == 'n') {
			tnode = ptr+5;
			ptr = audit_strsplit(NULL);
		} else
			tnode = NULL;


		ttype = ptr+5;


		ptr = audit_strsplit(NULL);
		if (ptr) {
			if (*(ptr+9) == '(')
				ptr+=9;
			else
				ptr = strchr(ptr, '(');
			if (ptr) {

				char *eptr;
				ptr++;
				eptr = strchr(ptr, ')');
				if (eptr)
					*eptr = 0;
				if (str2event(ptr, e)) {
					fprintf(stderr,
					  "Error extracting time stamp (%s)\n",
						ptr);
					return 0;
				} else if ((start_time && e->sec < start_time)
					|| (end_time && e->sec > end_time))
					return 0;
				else {
					if (tnode)
						e->node = strdup(tnode);
					e->type = audit_name_to_msg_type(ttype);
				}
				return 1;
			}

		}

	}

	return 0;
}
