epsf_define(GVJ_t *job)
{
    usershape_t *us;

    if (!EPSF_contents)
	return;
    for (us = dtfirst(EPSF_contents); us; us = dtnext(EPSF_contents, us)) {
	if (us->must_inline)
	    continue;
	gvprintf(job, "/user_shape_%d {\n", us->macro_id);
	gvputs(job, "%%BeginDocument:\n");
	epsf_emit_body(job, us);
	gvputs(job, "%%EndDocument\n");
	gvputs(job, "} bind def\n");
    }
}
