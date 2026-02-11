clientCloneReply(clientHttpRequest * http, HttpReply * orig_rep)
{
    HttpReply *rep = NULL;

    if (http->sc->entry->mem_obj == NULL || http->sc->entry->mem_obj->reply == NULL) {
	clientUnwindReply(http, NULL);
	return NULL;
    }

    rep = httpReplyClone(orig_rep);
    if (rep->pstate == psParsed) {

	clientBuildReplyHeader(http, rep);

	if (http->request->range)
	    httpStatusLineSet(&rep->sline, rep->sline.version,
		HTTP_PARTIAL_CONTENT, NULL);
    } else {

	clientUnwindReply(http, rep);
	return NULL;
    }
    return rep;
}
