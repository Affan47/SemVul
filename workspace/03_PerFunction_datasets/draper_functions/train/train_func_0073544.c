enquiry_response(struct PStack *st)
{
	if (test_bit(FLG_OWN_BUSY, &st->l2.flag))
		enquiry_cr(st, RNR, RSP, 1);
	else
		enquiry_cr(st, RR, RSP, 1);
	test_and_clear_bit(FLG_ACK_PEND, &st->l2.flag);
}
