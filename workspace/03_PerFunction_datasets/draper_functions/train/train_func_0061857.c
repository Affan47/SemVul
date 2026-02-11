set_68000_compa (struct uae_prefs *p, int compa)
{
	p->cpu_clock_multiplier = 2 << 8;
	switch (compa)
	{
	case 0:
		p->cpu_cycle_exact = p->blitter_cycle_exact = 1;
		break;
	case 1:
		break;
	case 2:
		p->cpu_compatible = 0;
		break;
	case 3:
		p->produce_sound = 2;
		p->cpu_compatible = 0;
		break;
	}
}
