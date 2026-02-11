setacl(const char *failmsg,int status)
{
    char body[1024];
    sprintf(body, "<D:acl xmlns:D='DAV:'>"
		   "<D:ace>"
	      	   "<D:principal>"
		   "<D:href>/users/test2</D:href>"
		   "</D:principal>"
		   "<D:grant>"
		   "<D:privilege><D:all/></D:privilege>"
		   "</D:grant>"
		   "</D:ace>"
		   "</D:acl>");
    ne_request *req = ne_request_create(i_session, "ACL", i_path);
    ne_set_request_body_buffer(req, body, strlen(body));
    ONNREQ(failmsg, ne_request_dispatch(req));
    if(status)
    	ONV(ne_get_status(req)->klass != 2, ("%s", failmsg));
    else
    	ONV(ne_get_status(req)->klass != 4, ("%s", failmsg));
    ne_request_destroy(req);
    return OK;
}
