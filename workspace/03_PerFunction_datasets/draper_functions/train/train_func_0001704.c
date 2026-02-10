jdns_packet_question_copy(const jdns_packet_question_t *a)
{
	jdns_packet_question_t *c = jdns_packet_question_new();
	if(a->qname)
		c->qname = jdns_string_copy(a->qname);
	c->qtype = a->qtype;
	c->qclass = a->qclass;
	return c;
}
