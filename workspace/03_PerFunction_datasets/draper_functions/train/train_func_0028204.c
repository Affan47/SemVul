kqdoom(pclient, pkq)

struct kproc		*pclient;
struct kreq		*pkq;

{
	struct kproc	*pdoom;
	struct kreply	reply;

	LAM_ZERO_ME(reply);
	lamlog_cond(("kernel (kqdoom): pid=%d target=%d signal=%d\n",
		     pclient->kp_pid,
		     pkq->kq_pid, pkq->kq_signal));

	if ((pdoom = kpfind(pkq->kq_pid)) == 0) {
		reply.kr_reply = ENOTPROCESS;
		reply.kr_signal = 0;
	} else if (pdoom->kp_flags & KIPROC) {
		reply.kr_reply = ESERVICE;
		reply.kr_signal = 0;
	} else if (pdoom == pclient) {
		reply.kr_reply = 0;
		reply.kr_signal = pkq->kq_signal;
	} else {

		if (pdoom->kp_state == KSREADY) {
			pdoom->kp_signal |= pkq->kq_signal;
			kpreempt(pdoom);
		} else {
			reply.kr_reply = EINTR;
			reply.kr_signal = pkq->kq_signal;
			kpdelete(&pblock, pdoom, (struct kproc *) 0);
			kpinsert(&pready, pdoom);
			pdoom->kp_state = KSREADY;

			if (pdoom->kp_msg.k_flags & KTRACE) {
				pdoom->kp_blktime = ttime() -
						pdoom->kp_blktime;
				reply.kr_blktime = pdoom->kp_blktime;
			}

			kio_reply(&reply, pdoom->kp_port);
			reply.kr_signal = 0;
		}

		reply.kr_reply = 0;
		reply.kr_signal = 0;
	}

	if (!(pclient->kp_flags & KIPROC)) {
		kio_reply(&reply, pclient->kp_port);
	}
}
