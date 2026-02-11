_cipc_kreq(preq, preply)

struct kreq		*preq;
struct kreply		*preply;

{
	if (preq->kq_req == KQSTATE) {
		ksnap(preq, preply);
	} else {


		if (aq_shove(prun->kp_kqueue, preq))
				lampanic("lamd (aq_shove)");


		preply->kr_reply = 0;
	}

	preply->kr_signal = 0;
	return(0);
}
