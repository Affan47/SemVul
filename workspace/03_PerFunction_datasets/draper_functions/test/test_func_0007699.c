aclget(void)
{
    struct results r = {0};

    PRECOND(acl_ok);

    r.result = 1;
    t_context("No responses returned");

    ONMREQ("PROPFIND", acl_uri,
	   ne_simple_propfind(i_session, acl_uri, NE_DEPTH_ZERO,
			      props, pg_results, &r));

    if (r.result) {
	return r.result;
    }

    return OK;
}
