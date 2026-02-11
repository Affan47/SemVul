sh2_recalc_irq(void)
{
	int irq = 0, vector = -1;
	int i, level;


	if((sh2.m[4]>>8) & sh2.m[4] & (ICF|OCFA|OCFB|OVF))
	{
		level = (sh2.m[0x18] >> 24) & 15;
		if(level > irq)
		{
			int mask = (sh2.m[4]>>8) & sh2.m[4];
			irq = level;
			if(mask & ICF)
				vector = (sh2.m[0x19] >> 8) & 0x7f;
			else if(mask & (OCFA|OCFB))
				vector = sh2.m[0x19] & 0x7f;
			else
				vector = (sh2.m[0x1a] >> 24) & 0x7f;
		}
	}


	for(i=0; i<2; i++)
	{
		if((sh2.m[0x63+4*i] & 6) == 6) {
			level = (sh2.m[0x38] >> 8) & 15;
			if(level > irq) {
				irq = level;
				vector = (sh2.m[0x68+2*i] >> 24) & 0x7f;
			}
		}
	}

	sh2.internal_irq_level = irq;
	sh2.internal_irq_vector = vector;
	sh2.test_irq = 1;
}
