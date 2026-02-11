borg_attack_aux_ring(int ring_name, int rad, int dam, int typ)
{
    int b_n;


    if (borg_skill[BI_ISBLIND] || borg_skill[BI_ISCONFUSED] || borg_skill[BI_ISIMAGE]) return (0);


    if (borg_simulate && (randint0(100) < 2)) return (0);


    if (!borg_equips_ring(ring_name)) return (0);


    b_n = borg_launch_bolt(rad, dam, typ, MAX_RANGE, 0);


    if (borg_simulate) return (b_n);


    (void)borg_activate_ring(ring_name);


    borg_keypress('5');


    successful_target = -1;


    return (b_n);
}
