parse_groups(const char *groups, message_data_t *msg)
{
    const char *p;
    char *rcpt = NULL;
    size_t n;

    for (p = groups;; p += n) {

	while (p && *p && (Uisspace(*p) || *p == ',')) p++;

	if (!p || !*p) return 0;

	if (!(msg->rcpt_num % RCPT_GROW)) {
	    msg->rcpt = (char **)
		xrealloc(msg->rcpt, (msg->rcpt_num + RCPT_GROW + 1) *
			 sizeof(char *));
	}


	n = strcspn(p, ", \t");
	rcpt = xrealloc(rcpt, strlen(newsprefix) + n + 1);
	if (!rcpt) return -1;


	sprintf(rcpt, "%.*s", (int) n, p);


	if (!is_newsgroup(rcpt)) continue;


	if (!mlookup(rcpt, NULL, NULL, NULL)) {
	    msg->rcpt[msg->rcpt_num] = rcpt;
	    msg->rcpt_num++;
	    msg->rcpt[msg->rcpt_num] = rcpt = NULL;
	}
    }


}
