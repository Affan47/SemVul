borg_zap_rod(int sval)
{
    int i, lev, fail;
	int skill;


    i = borg_slot(TV_ROD, sval);


    if (i < 0) return (FALSE);


    if (!borg_items[i].pval) return (FALSE);


    lev = (borg_items[i].level);


    skill = borg_skill[BI_DEV];


    if (borg_skill[BI_ISCONFUSED]) skill = skill * 75 / 100;


    fail = 100 * ((skill - lev) - (141 - 1)) / ((lev - skill) - (100 - 10));


    if (sval != SV_ROD_RECALL)
    {
		if (fail > 500) return (FALSE);
	}


    borg_note(format("# Zapping %s.", borg_items[i].desc));


    borg_keypress('z');
    borg_keypress(I2A(i));


    return (TRUE);
}
