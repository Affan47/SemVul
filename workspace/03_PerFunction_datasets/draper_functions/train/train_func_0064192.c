propfind_allprop_include(void)
{
    char body[512];

    sprintf(body,  "<D:allprop />"
                   "<D:include>"
                   "<D:acl />"
                   "<D:resource-id />"
                   "</D:include>");

	struct results r = {0};
	incliveprops=1;
	r.ph = ne_propfind_create(i_session,prop_uri, NE_DEPTH_ZERO,"PROPFIND");
	ONMREQ("PROPFIND", prop_uri,
		ne_propfind(r.ph,body,pg_results_allprop, &r, ne_propfind_method));
	ne_propfind_destroy(r.ph);
	incliveprops=0;
        return OK;
}
