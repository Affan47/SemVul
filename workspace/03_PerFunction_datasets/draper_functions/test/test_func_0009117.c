enquiry_response(struct layer2 *l2)
{
	if (test_bit(FLG_OWN_BUSY, &l2->flag))
		enquiry_cr(l2, RNR, RSP, 1);
	else
		enquiry_cr(l2, RR, RSP, 1);
	test_and_clear_bit(FLG_ACK_PEND, &l2->flag);
}
