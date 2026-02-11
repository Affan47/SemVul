TclWeb_SetHeaderType(char *header, TclWebRequest *req)
{

    if(req->headers_set)
        return TCL_ERROR;


    ap_set_content_type(req->req,apr_pstrdup(req->req->pool, header));
    req->headers_set = 1;
    return TCL_OK;
}
