cache_proc(SERVER *server)
{
    char	*buffer = NULL;

    if (!server) {
	current_done(False);
	snarfing = False;
	state = CacheStateNone;
	return False;
    }

    do {
	switch (state) {
	case CacheStateNone:
	    return start_article(server);
	case CacheStateSentArticle:
	    buffer = server_get_line(server);
	    if (!buffer)
		break;

	    if (atoi(buffer) != NNTP_OK_ARTICLE) {
		if (snarfing)
		    snarfing = False;
		else
		    current_done(False);
		return start_article(server);
	    }

	    state = CacheStateDoingArticle;
	    break;
	case CacheStateDoingArticle:
	    buffer = server_get_line(server);
	    if (!buffer)
		break;

	    if (fp)
		fprintf(fp, "%s\r\n", buffer);

	    if (!IS_DOT(buffer))
		break;

	    if (snarfing)
		snarfing = False;
	    else
		current_done(True);
	    state = CacheStateNone;

	    return False;
	}
    } while (buffer);

    return True;
}
