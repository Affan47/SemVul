pan_sess(const struct sess *sp)
{
	const char *stp, *hand;

	VSB_printf(pan_vsp, "sp = %p {\n", sp);
	VSB_printf(pan_vsp,
	    "  fd = %d, id = %u, xid = %u,\n",
	    sp->fd, sp->vsl_id & VSL_IDENTMASK, sp->req->xid);
	VSB_printf(pan_vsp, "  client = %s %s,\n",
	    sp->addr ? sp->addr : "?.?.?.?",
	    sp->port ? sp->port : "?");
	switch (sp->step) {
#define STEP(l, u, arg) case STP_##u: stp = "STP_" #u; break;
#include "tbl/steps.h"
#undef STEP
		default: stp = NULL;
	}
	hand = VCL_Return_Name(sp->req->handling);
	if (stp != NULL)
		VSB_printf(pan_vsp, "  step = %s,\n", stp);
	else
		VSB_printf(pan_vsp, "  step = 0x%x,\n", sp->step);
	if (hand != NULL)
		VSB_printf(pan_vsp, "  handling = %s,\n", hand);
	else
		VSB_printf(pan_vsp, "  handling = 0x%x,\n", sp->req->handling);
	if (sp->req->err_code)
		VSB_printf(pan_vsp,
		    "  err_code = %d, err_reason = %s,\n", sp->req->err_code,
		    sp->req->err_reason ? sp->req->err_reason : "(null)");

	VSB_printf(pan_vsp, "  restarts = %d, esi_level = %d\n",
	    sp->req->restarts, sp->req->esi_level);

	if (sp->wrk->busyobj != NULL)
		pan_busyobj(sp->wrk->busyobj);

	pan_ws(sp->req->ws, 2);
	pan_http("req", sp->req->http, 2);
	if (sp->req->resp->ws != NULL)
		pan_http("resp", sp->req->resp, 4);

	if (sp->wrk != NULL)
		pan_wrk(sp->wrk);

	if (VALID_OBJ(sp->req->vcl, VCL_CONF_MAGIC))
		pan_vcl(sp->req->vcl);

	if (VALID_OBJ(sp->req->obj, OBJECT_MAGIC))
		pan_object(sp->req->obj);

	VSB_printf(pan_vsp, "},\n");
}
