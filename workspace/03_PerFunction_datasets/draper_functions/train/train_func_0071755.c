borg_defend_aux_inviso(int p1)
{
    int fail_allowed = 25;
    borg_grid *ag = &borg_grids[c_y][c_x];


	if (borg_skill[BI_ISFORGET] || borg_skill[BI_ISBLIND] || borg_skill[BI_ISCONFUSED] || borg_see_inv)
        return (0);


    if (borg_t > need_see_inviso + 5) return (0);


    if (p1 > avoidance * 2) return (0);


    if (-1 == borg_slot(TV_POTION,SV_POTION_DETECT_INVIS)  &&
        -1 == borg_slot(TV_SCROLL,SV_SCROLL_DETECT_INVIS) &&
        !borg_equips_staff_fail(SV_STAFF_DETECT_INVIS) &&
        !borg_equips_staff_fail(SV_STAFF_DETECT_EVIL) &&
        !borg_prayer_okay_fail(2, 3, fail_allowed) &&
        !borg_prayer_okay_fail(5, 0, fail_allowed) &&
        !borg_spell_okay_fail(2, 6, fail_allowed))
        return (0);


    if (!(ag->info & BORG_GLOW) && !borg_skill[BI_CURLITE]) return (0);


    if (borg_simulate) return (10);


    if (borg_prayer(5, 0) ||
    	borg_spell_fail(2, 6, fail_allowed) ||
		borg_read_scroll(SV_SCROLL_DETECT_INVIS) ||
        borg_use_staff(SV_STAFF_DETECT_INVIS) ||
        borg_use_staff(SV_STAFF_DETECT_EVIL))
    {
        borg_see_inv = 3000;
        return (10);
    }
    if (borg_quaff_potion(SV_POTION_DETECT_INVIS))
    {
        borg_see_inv = 18000;
        borg_no_rest_prep = 18000;
        return (10);
    }

    if (borg_prayer_fail(2, 3, fail_allowed))
    {
        borg_see_inv = 30000;
        borg_no_rest_prep = 16000;
        return (10);
    }


    return (0);

}
