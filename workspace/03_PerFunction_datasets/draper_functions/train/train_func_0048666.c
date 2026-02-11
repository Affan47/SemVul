built_in_prefs (struct uae_prefs *p, int model, int config, int compa, int romcheck)
{
	int v = 0;

	buildin_default_prefs (p);
	switch (model)
	{
	case 0:
		v = bip_a500 (p, config, compa, romcheck);
		break;
	case 1:
		v = bip_a500p (p, config, compa, romcheck);
		break;
	case 2:
		v = bip_a600 (p, config, compa, romcheck);
		break;
	case 3:
		v = bip_a1000 (p, config, compa, romcheck);
		break;
	case 4:
		v = bip_a1200 (p, config, compa, romcheck);
		break;
	case 5:
		v = bip_a3000 (p, config, compa, romcheck);
		break;
	case 6:
		v = bip_a4000 (p, config, compa, romcheck);
		break;
	case 7:
		v = bip_a4000t (p, config, compa, romcheck);
		break;
	case 8:
		v = bip_cd32 (p, config, compa, romcheck);
		break;
	case 9:
		v = bip_cdtv (p, config, compa, romcheck);
		break;
	case 10:
		v = bip_arcadia (p, config , compa, romcheck);
		break;
	case 11:
		v = bip_super (p, config, compa, romcheck);
		break;
	}
	if ((p->cpu_model >= 68020 || !p->cpu_cycle_exact) && !p->immediate_blits)
		p->waiting_blits = 1;
	return v;
}
