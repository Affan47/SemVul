job_recvmsg(const struct nihdr *ni, struct remote *rp)
{
	USHORT		act = ntohs(ni->code);
	Hashspq		*hjp;
	struct	spr_req		rq;
	struct	sp_omsg		orq;

	READ_SOCK(rp, orq);

	rq.spr_mtype = MT_SCHED;
	rq.spr_un.o.spr_pid = Netm_pid;
	rq.spr_un.o.spr_seq = 0;
	rq.spr_un.o.spr_arg1 = ntohl(orq.spr_arg1);
	rq.spr_un.o.spr_arg2 = ntohl(orq.spr_arg2);
	rq.spr_un.o.spr_jobno = ntohl(orq.spr_jobno);
	rq.spr_un.o.spr_netid = rp->hostid;

	switch  (rq.spr_un.o.spr_act = act)  {
	default:
		if  (!(hjp = ver_job((slotno_t) ntohl(orq.spr_jpslot), (jobno_t) ntohl(orq.spr_jobno))))
			return;
		rq.spr_un.o.spr_jpslot = hjp - Job_seg.jlist;
		break;


	case  SO_PROPOSE:
		rq.spr_un.o.spr_jpslot = ntohl(orq.spr_jpslot);
		break;

	case  SO_PROP_OK:
	case  SO_PROP_NOK:
	case  SO_PROP_DEL:


		rq.spr_un.o.spr_jpslot = ntohl(orq.spr_arg1);
		break;
	}
	push_msg((struct msgbuf *) &rq, sizeof(struct sp_omsg));
}
