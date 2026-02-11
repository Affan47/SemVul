puton_q(const unsigned jind, const LONG after)
{
	LONG	nxt;

	Job_seg.jlist[jind].q_prv = after;

	if  (after < 0L)  {

		nxt = Job_seg.dptr->js_q_head;
		Job_seg.dptr->js_q_head = (LONG) jind;
	}
	else  {
		nxt = Job_seg.jlist[after].q_nxt;
		Job_seg.jlist[after].q_nxt = (LONG) jind;
	}

	Job_seg.jlist[jind].q_nxt = nxt;
	if  (nxt < 0L)
		Job_seg.dptr->js_q_tail = (LONG) jind;
	else
		Job_seg.jlist[nxt].q_prv = (LONG) jind;
}
