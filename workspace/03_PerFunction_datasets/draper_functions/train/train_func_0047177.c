borg_twitchy(void)
{
    int dir = 5;


    borg_note("# Twitchy!");


    if (borg_caution_phase(15, 2) &&
       (borg_spell_fail(0, 2, 40) ||
        borg_prayer_fail(4, 0, 40) ||
        borg_activate_artifact(EFF_TELE_PHASE, INVEN_BODY)||
        borg_activate_artifact(EFF_TELE_LONG,INVEN_OUTER) ||
        borg_read_scroll(SV_SCROLL_PHASE_DOOR) ))
    {

        return (TRUE);
    }

	while (dir == 5 || dir == 0)
	{
		dir = randint0(9);
	}


    g_x = c_x + ddx[dir];
    g_y = c_y + ddy[dir];


    borg_keypress(I2D(dir));


    return (TRUE);
}
