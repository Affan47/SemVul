gvrender_ellipse(GVJ_t * job, pointf * pf, int n, int filled)
{
    gvrender_engine_t *gvre = job->render.engine;

    if (gvre) {
	if (gvre->ellipse && job->obj->pen != PEN_NONE) {
	    pointf af[2];


	    af[0].x = (pf[0].x + pf[1].x) / 2.;
	    af[0].y = (pf[0].y + pf[1].y) / 2.;

	    af[1] = pf[1];

	    if (!(job->flags & GVRENDER_DOES_TRANSFORM))
		gvrender_ptf_A(job, af, af, 2);
	    gvre->ellipse(job, af, filled);
	}
    }
}
