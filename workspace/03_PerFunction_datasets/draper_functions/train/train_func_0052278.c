jb_process(const int bytes, struct sp_xjmsg *req)
{
	struct	joborptr  *pp;
	struct	spq	injob;

	if  (bytes < sizeof(struct sp_xjmsg))  {
		disp_arg[9] = bytes;
		report(1111);
	}

	pp = fetch_ptr();
	BLOCK_COPY(&injob, &pp->jorp_un.q, sizeof(struct spq));
	if  (pp->jorp_sender != req->spr_pid)  {
		nfreport(8119);
		unlockxbuf();
		return;
	}
	unlockxbuf();

	switch	(req->spr_act)  {
	default:
		disp_arg[9] = req->spr_act;
		report(1109);

	case  SJ_ENQ:
		enqueue(req, &injob);
		break;

	case  SJ_CHNG:
		chjob(req, &injob);
		break;

#ifdef	NETWORK_VERSION
	case  SJ_CHANGEDJOB:
		remchjob(req, &injob);
		break;

	case  SJ_JUNASSIGN:
		unassign_job(req, &injob);
		break;

	case  SJ_JUNASSIGNED:
		unassign_remjob(req, &injob);
		break;
#endif
	}
}
