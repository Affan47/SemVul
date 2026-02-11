get_irq_nr(struct cpssp *cpssp)
{
	int irq;

	switch (cpssp->mixer.reg[0x80] & 0x0f) {
	case 0x1:
		irq = 0;
		break;
	case 0x2:
		irq = 1;
		break;
	case 0x4:
		irq = 2;
		break;
	case 0x8:
		irq = 3;
		break;
	default:

		assert(0);
	}

	return irq;
}
