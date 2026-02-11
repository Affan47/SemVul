tei_id_test_dup(struct FsmInst *fi, int event, void *arg)
{
	struct PStack *ost, *st = fi->userdata;
	struct sk_buff *skb = arg;
	int tei, ri;

	ri = ((unsigned int) skb->data[1] << 8) + skb->data[2];
	tei = skb->data[4] >> 1;
	if (st->ma.debug)
		st->ma.tei_m.printdebug(&st->ma.tei_m,
					"foreign identity assign ri %d tei %d", ri, tei);
	if ((ost = findtei(st, tei))) {
		if (ri != ost->ma.ri) {
			st->ma.tei_m.printdebug(&st->ma.tei_m,
						"possible duplicate assignment tei %d", tei);
			FsmEvent(&ost->ma.tei_m, EV_VERIFY, NULL);
		}
	}
}
