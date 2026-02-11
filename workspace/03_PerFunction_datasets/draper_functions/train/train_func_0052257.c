job_recvbcast(const struct nihdr *ni, struct remote *rp)
{
	USHORT			act = ntohs(ni->code);
	struct	spr_req		rq;
	struct	sp_jmsg		jrq;
	struct	spq		injob;

	READ_SOCK(rp, jrq);

	switch  (act)  {
	case  SJ_ENQ:
		rq.spr_mtype = MT_SCHED;
		rq.spr_un.j.spr_act = SJ_ENQ;
		rq.spr_un.j.spr_pid = Netm_pid;
		rq.spr_un.j.spr_seq = 0;
		rq.spr_un.j.spr_netid = rp->hostid;
		unpack_job(&injob, &jrq.spr_q);
		injob.spq_rslot = ntohl(jrq.spr_jslot);
		push_jmsg(&rq, &injob);
		break;

	case  SJ_CHANGEDJOB:
	case  SJ_JUNASSIGNED:
		rq.spr_mtype = MT_SCHED;
		rq.spr_un.j.spr_act = act;
		rq.spr_un.j.spr_pid = Netm_pid;
		rq.spr_un.j.spr_seq = 0;
		rq.spr_un.j.spr_netid = rp->hostid;
		unpack_job(&injob, &jrq.spr_q);
		rq.spr_un.j.spr_jslot = ntohl(jrq.spr_jslot);
		push_jmsg(&rq, &injob);
		break;

	case  SO_DEQUEUED:
	case  SO_LOCASSIGN:
		rq.spr_mtype = MT_SCHED;
		rq.spr_un.o.spr_act = act;
		rq.spr_un.o.spr_pid = Netm_pid;
		rq.spr_un.o.spr_seq = 0;
		rq.spr_un.o.spr_netid = rp->hostid;
		rq.spr_un.o.spr_jpslot = ntohl(jrq.spr_jslot);
		push_msg((struct msgbuf *) &rq, sizeof(struct sp_omsg));
	}
}
