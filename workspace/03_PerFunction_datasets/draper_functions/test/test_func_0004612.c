sb16_set_irq_hw(sb_devc * devc, int level)
{
	int ival;

	switch (level)
	{
		case 5:
			ival = 2;
			break;
		case 7:
			ival = 4;
			break;
		case 9:
			ival = 1;
			break;
		case 10:
			ival = 8;
			break;
		default:
			printk(KERN_ERR "SB16: Invalid IRQ%d\n", level);
			return 0;
	}
	sb_setmixer(devc, IRQ_NR, ival);
	return 1;
}
