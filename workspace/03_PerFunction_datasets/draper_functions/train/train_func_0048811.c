getP4PMmultiplier(void)
{
	unsigned int msr_lo, msr_hi;
	float coef;


	if (cpu_id.type == 6) {
		if((cpu_id.feature_flag >> 7) & 1) {
			rdmsr(0x198, msr_lo, msr_hi);
			coef = ((msr_lo >> 8) & 0x1F);
			if ((msr_lo >> 14) & 0x1) { coef = coef + 0.5f; }
		} else {
			rdmsr(0x2A, msr_lo, msr_hi);
			coef = (msr_lo >> 22) & 0x1F;
		}
	}
	else
	{
		if (cpu_id.model < 2)
		{
			rdmsr(0x2A, msr_lo, msr_hi);
			coef = (msr_lo >> 8) & 0xF;
			coef = p4model1ratios[(int)coef];
		}
		else
		{
			rdmsr(0x2C, msr_lo, msr_hi);
			coef = (msr_lo >> 24) & 0x1F;
		}
	}
	return coef;
}
