chjob(struct sp_xjmsg *rq, struct spq *newj)
{
	Hashspq		*hjp;
	struct  spq	*dest;

	if  (rq->spr_jslot >= Job_seg.dptr->js_maxjobs)
		return;
	hjp = &Job_seg.jlist[rq->spr_jslot];
	dest = &hjp->j;

#ifdef	NETWORK_VERSION


	if  (dest->spq_netid)  {
		job_sendupdate(dest, newj, SJ_CHNG);
		return;
	}

#endif

	copy_minor(dest, newj);
	Job_seg.Last_ser++;
	qchanges++;
	Job_seg.dptr->js_serial++;

	if  (printing(dest))  {
#ifdef	NETWORK_VERSION
		if  (!(dest->spq_jflags & SPQ_LOCALONLY))
			job_broadcast(hjp, SJ_CHANGEDJOB);
#endif
		return;
	}

	jobs_lock();
	copy_major(rq->spr_jslot, dest, newj);


	if  (!Network_ok)
		dest->spq_jflags |= SPQ_LOCALONLY;

#ifdef	NETWORK_VERSION


	if  ((dest->spq_jflags & SPQ_LOCALONLY) != (newj->spq_jflags & SPQ_LOCALONLY))  {
		if  (dest->spq_jflags & SPQ_LOCALONLY)  {
			dest->spq_jflags &= ~SPQ_LOCALONLY;
			job_broadcast(hjp, SJ_ENQ);
		}
		else  {
			dest->spq_jflags |= SPQ_LOCALONLY;
			job_broadcast(hjp, SO_DEQUEUED);
		}
	}
	else  if  (!(dest->spq_jflags & SPQ_LOCALONLY))
		job_broadcast(hjp, SJ_CHANGEDJOB);
#endif

	jobs_unlock();
}
