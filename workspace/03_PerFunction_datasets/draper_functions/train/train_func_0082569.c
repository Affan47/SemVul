ossl_x509req_set_attributes(VALUE self, VALUE ary)
{
    X509_REQ *req;
    X509_ATTRIBUTE *attr;
    int i;
    VALUE item;

    Check_Type(ary, T_ARRAY);
    for (i=0;i<RARRAY_LEN(ary); i++) {
	OSSL_Check_Kind(RARRAY_PTR(ary)[i], cX509Attr);
    }
    GetX509Req(self, req);
    sk_X509_ATTRIBUTE_pop_free(req->req_info->attributes, X509_ATTRIBUTE_free);
    req->req_info->attributes = NULL;
    for (i=0;i<RARRAY_LEN(ary); i++) {
	item = RARRAY_PTR(ary)[i];
	attr = DupX509AttrPtr(item);
	if (!X509_REQ_add1_attr(req, attr)) {
	    ossl_raise(eX509ReqError, NULL);
	}
    }
    return ary;
}
