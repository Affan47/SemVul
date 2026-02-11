cmd_search(char *tag, int usinguid)
{
    int c;
    int charset = 0;
    struct searchargs *searchargs;
    clock_t start = clock();
    char mytime[100];
    int n;

    if (backend_current) {

	const char *cmd = usinguid ? "UID Search" : "Search";

	prot_printf(backend_current->out, "%s %s ", tag, cmd);
	if (!pipe_command(backend_current, 65536)) {
	    pipe_including_tag(backend_current, tag, 0);
	}
	return;
    }


    searchargs = (struct searchargs *)xzmalloc(sizeof(struct searchargs));
    searchargs->tag = tag;
    c = getsearchprogram(tag, searchargs, &charset, 1);
    if (c == EOF) {
	eatline(imapd_in, ' ');
	freesearchargs(searchargs);
	return;
    }

    if (c == '\r') c = prot_getc(imapd_in);
    if (c != '\n') {
	prot_printf(imapd_out, "%s BAD Unexpected extra arguments to Search\r\n", tag);
	eatline(imapd_in, c);
	freesearchargs(searchargs);
	return;
    }

    if (charset == -1) {
	prot_printf(imapd_out, "%s NO %s\r\n", tag,
	       error_message(IMAP_UNRECOGNIZED_CHARSET));
    }
    else {
	n = index_search(imapd_index, searchargs, usinguid);
	snprintf(mytime, sizeof(mytime), "%2.3f",
		 (clock() - start) / (double) CLOCKS_PER_SEC);
	prot_printf(imapd_out, "%s OK %s (%d msgs in %s secs)\r\n", tag,
		    error_message(IMAP_OK_COMPLETED), n, mytime);
    }

    freesearchargs(searchargs);
}
