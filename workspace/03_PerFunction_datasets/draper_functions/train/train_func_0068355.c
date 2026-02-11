borg_perma_aux_resist_f(void)
{
    int cost = 0;
    int fail_allowed = 5;
    borg_magic *as;


    if (unique_on_level) fail_allowed = 10;
    if (borg_fighting_unique) fail_allowed = 15;

    if (borg_skill[BI_TRFIRE] || !unique_on_level)
        return (0);

    if (borg_skill[BI_IFIRE]) return (0);

    if (!borg_spell_okay_fail(4, 1, fail_allowed))
        return (0);


    if (borg_spell_okay_fail(4, 3, fail_allowed)) return (0);


    as = &borg_magics[4][1];
    cost = as->power;


    if (cost >= borg_skill[BI_CURSP] /20) return (0);


    if (borg_simulate) return (1);


    if (borg_spell_fail(4, 1, fail_allowed) )
    {

	    borg_no_rest_prep = 3000;


        return (1);
    }


    return (0);
}
