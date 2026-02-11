wb_preq(const struct pkt_preq *preq, u_int len)
{
	printf(" wb-preq:");
	if (len < sizeof(*preq) || (u_char *)(preq + 1) > snapend)
		return (-1);

	printf(" need %u/%s:%u",
	       EXTRACT_32BITS(&preq->pp_low),
	       ipaddr_string(&preq->pp_page.p_sid),
	       EXTRACT_32BITS(&preq->pp_page.p_uid));
	return (0);
}
