prepare_setup_packet(struct r8a66597 *r8a66597,
				 struct r8a66597_td *td)
{
	int i;
	__le16 *p = (__le16 *)td->urb->setup_packet;
	unsigned long setup_addr = USBREQ;

	r8a66597_write(r8a66597, make_devsel(td->address) | td->maxpacket,
		       DCPMAXP);
	r8a66597_write(r8a66597, ~(SIGN | SACK), INTSTS1);

	for (i = 0; i < 4; i++) {
		r8a66597_write(r8a66597, le16_to_cpu(p[i]), setup_addr);
		setup_addr += 2;
	}
	r8a66597_write(r8a66597, SUREQ, DCPCTR);
}
