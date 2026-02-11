propfind_returns_wellformed(const char *msg, const char *body, char *request)
{
    ne_xml_parser *p = ne_xml_create();
    ne_request *req = ne_request_create(i_session, request, prop_uri);

    ne_set_request_body_buffer(req, body, strlen(body));

    ne_add_response_body_reader(req, ne_accept_207, ne_xml_parse_v, p);
    ONMREQ(request, prop_uri, ne_request_dispatch(req));

    ONV(ne_get_status(req)->code != 207, ("%s", msg));
    ONV(ne_get_status(req)->klass == 4, ("%s", msg));
    ONV(ne_xml_failed(p), ("%s response %s was not well-formed: %s",
                           request, msg, ne_xml_get_error(p)));

    ne_xml_destroy(p);
    ne_request_destroy(req);
    return OK;
}
