happy_meal_bb_write(struct happy_meal *hp,
				void __iomem *tregs, int reg,
				unsigned short value)
{
	u32 tmp;
	int i;

	ASD(("happy_meal_bb_write: reg=%d value=%x\n", reg, value));


	hme_write32(hp, tregs + TCVR_BBOENAB, 1);


	for (i = 0; i < 32; i++)
		BB_PUT_BIT(hp, tregs, 1);


	BB_PUT_BIT(hp, tregs, 0);
	BB_PUT_BIT(hp, tregs, 1);
	BB_PUT_BIT(hp, tregs, 0);
	BB_PUT_BIT(hp, tregs, 1);


	tmp = (hp->paddr & 0xff);
	for (i = 4; i >= 0; i--)
		BB_PUT_BIT(hp, tregs, ((tmp >> i) & 1));


	tmp = (reg & 0xff);
	for (i = 4; i >= 0; i--)
		BB_PUT_BIT(hp, tregs, ((tmp >> i) & 1));


	BB_PUT_BIT(hp, tregs, 1);
	BB_PUT_BIT(hp, tregs, 0);

	for (i = 15; i >= 0; i--)
		BB_PUT_BIT(hp, tregs, ((value >> i) & 1));


	hme_write32(hp, tregs + TCVR_BBOENAB, 0);
}
