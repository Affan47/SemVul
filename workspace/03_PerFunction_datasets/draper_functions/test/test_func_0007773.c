uip_unlisten(struct uip_stack *ustack, u16_t port)
{
	u8_t c;

	for (c = 0; c < UIP_LISTENPORTS; ++c) {
		if (ustack->uip_listenports[c] == port) {
			ustack->uip_listenports[c] = 0;
			return;
		}
	}
}
