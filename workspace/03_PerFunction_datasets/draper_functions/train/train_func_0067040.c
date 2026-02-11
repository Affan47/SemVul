VRT_count(const struct sess *sp, unsigned u)
{

	if (sp == NULL)
		return;
	CHECK_OBJ_NOTNULL(sp, SESS_MAGIC);
	if (cache_param->vcl_trace)
		WSP(sp, SLT_VCL_trace, "%u %u.%u", u,
		    sp->req->vcl->ref[u].line, sp->req->vcl->ref[u].pos);
}
