mcs_read_domain_mcspdu_header(STREAM* s, enum DomainMCSPDU* domainMCSPDU, int* length)
{
	uint8 choice;
	enum DomainMCSPDU MCSPDU;

	*length = tpkt_read_header(s);

	if (tpdu_read_data(s) == 0)
		return False;

	MCSPDU = *domainMCSPDU;
	per_read_choice(s, &choice);
	*domainMCSPDU = (choice >> 2);

	if (*domainMCSPDU != MCSPDU)
		return False;

	return True;
}
