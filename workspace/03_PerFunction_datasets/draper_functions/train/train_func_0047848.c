unassign_job(struct sp_xjmsg *rq, struct spq *newj)
{
	Hashspq		*hjp;
	struct  spq	*dest;

	if  (rq->spr_jslot >= Job_seg.dptr->js_maxjobs)
		return;
	hjp = &Job_seg.jlist[rq->spr_jslot];
	dest = &hjp->j;
	dest->spq_cps = newj->spq_cps;
	dest->spq_jflags = newj->spq_jflags;
	dest->spq_dflags = newj->spq_dflags;
	dest->spq_sflags &= SPQ_WARNED;
	dest->spq_haltat = newj->spq_haltat;
	dest->spq_pslot = -1;
	if  (dest->spq_cps == 0)
		dest->spq_time = time((time_t *) 0);
	job_broadcast(hjp, SJ_JUNASSIGNED);
	Job_seg.Last_ser++;
	qchanges++;
	Job_seg.dptr->js_serial++;
}
