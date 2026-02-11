xmlrpc_doc_parse(Octstr *post_body, int d_type)
{
    XMLRPCDocument *xrdoc = xmlrpc_doc_create();
    xmlDocPtr pDoc;
    size_t size;
    char *body;

    if (post_body == NULL) {
        xrdoc->parse_status = XMLRPC_XMLPARSE_FAILED;
        xrdoc->parse_error = octstr_create("XMLRPC: (null) XML document given.");
        return xrdoc;
    }
    xrdoc->d_type = d_type;

    octstr_strip_blanks(post_body);
    octstr_shrink_blanks(post_body);
    size = octstr_len(post_body);
    body = octstr_get_cstr(post_body);


    pDoc = xmlParseMemory(body, size);
    if (!pDoc) {
        xrdoc->parse_status = XMLRPC_XMLPARSE_FAILED;
        xrdoc->parse_error = octstr_create("XMLRPC: not valid XML document given.");
        return xrdoc;
    }
    parse_document(pDoc, xrdoc);
    xmlFreeDoc(pDoc);

    return xrdoc;
}
