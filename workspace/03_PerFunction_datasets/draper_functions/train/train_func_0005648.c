parse_irq(u_char *p, u_char *q, cistpl_irq_t *irq)
{
	if (p == q)
		return NULL;
	irq->IRQInfo1 = *p; p++;
	if (irq->IRQInfo1 & IRQ_INFO2_VALID) {
		if (p+2 > q)
			return NULL;
		irq->IRQInfo2 = (p[1]<<8) + p[0];
		p += 2;
	}
	return p;
}
