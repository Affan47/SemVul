borg_attack_aux_launch_dragon(void)
{
    int b_n = 0;

    int k , b_k = -1;
    int d , b_d = -1;

    borg_item *bow = &borg_items[INVEN_BOW];


    for (k = QUIVER_START; k < QUIVER_END; k++)
    {
        borg_item *item = &borg_items[k];


        if (!item->iqty) continue;

        if (item->sval == SV_AMMO_HEAVY) continue;
        if (!of_has(item->flags, OF_SLAY_DRAGON) &&
			!of_has(item->flags, OF_KILL_DRAGON)) continue;


        if (item->tval != my_ammo_tval) continue;


        if (item->value <= 0) continue;


        d = (item->dd * (item->ds + 1) / 2);
        d = d + item->to_d + bow->to_d;
        d = d * my_ammo_power * borg_skill[BI_SHOTS];


        if (d <= 0) continue;

        if ((b_k >=0) && (d<= b_d)) continue;

        b_k = k;
        b_d = d;
    }


    if (b_k < 0) return (0);


    if (borg_skill[BI_ISBLIND] || borg_skill[BI_ISCONFUSED] || borg_skill[BI_ISIMAGE]) return (0);


    b_n = borg_launch_bolt(0, b_d, GF_ARROW_DRAGON, 6 + 2 * my_ammo_power, b_k);


    if (borg_simulate) return (b_n);


    borg_note(format("# Firing dragon branded missile '%s'",
                     borg_items[b_k].desc));


    borg_keypress('f');


    borg_keypress((b_k+73));


    borg_keypress('5');


    successful_target = -2;


    return (b_n);
}
