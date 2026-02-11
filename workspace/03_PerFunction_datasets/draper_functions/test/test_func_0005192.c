TclWeb_GetHeaderVars(Tcl_Obj *headersvar, TclWebRequest *req)
{
    int i;

    apr_array_header_t *hdrs_arr;
    apr_table_entry_t  *hdrs;
    Tcl_Obj *key;
    Tcl_Obj *val;

    TclWeb_InitEnvVars( req );

    Tcl_IncrRefCount(headersvar);

    hdrs_arr = (apr_array_header_t*) apr_table_elts(req->req->headers_in);
    hdrs = (apr_table_entry_t *) hdrs_arr->elts;
    for (i = 0; i < hdrs_arr->nelts; ++i)
    {
	if (!hdrs[i].key)
	    continue;

	key = TclWeb_StringToUtfToObj(hdrs[i].key, req);
	val = TclWeb_StringToUtfToObj(hdrs[i].val, req);
	Tcl_IncrRefCount(key);
	Tcl_IncrRefCount(val);


        Tcl_ObjSetVar2(req->interp, headersvar, key, val, 0);
 	Tcl_DecrRefCount(key);
	Tcl_DecrRefCount(val);
    }


    Tcl_DecrRefCount(headersvar);
    return TCL_OK;
}
