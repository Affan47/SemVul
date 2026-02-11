borg_defend_aux_berserk( int p1 )
{
    int fail_allowed = 15;


    if (borg_berserk)
        return (0);


    if (borg_skill[BI_ISBLIND] || borg_skill[BI_ISCONFUSED] || borg_skill[BI_ISFORGET]) return (0);

	if (!borg_spell_okay_fail(7, 1, fail_allowed ) &&
        -1 == borg_slot(TV_POTION, SV_POTION_BERSERK_STRENGTH) &&
        !borg_equips_artifact(EFF_BERSERKER, INVEN_WIELD))
        return (0);


    if ((p1 > avoidance * 1 / 10 && p1 < avoidance * 5 / 10) ||
         (borg_fighting_unique && p1 < avoidance * 7 / 10))
    {


        if (borg_simulate) return (5);


        if (borg_spell(7, 1) ||
        	borg_activate_artifact(EFF_BERSERKER, INVEN_WIELD) ||
            borg_quaff_potion(SV_POTION_BERSERK_STRENGTH))
             return 2;
    }

    return (0);
}
