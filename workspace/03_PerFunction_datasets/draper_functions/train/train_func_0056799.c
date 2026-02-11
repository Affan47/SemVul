SP_level_spellpoint_cost(object *caster, object *spell, int flags) {
    int sp, grace, level = caster_level(caster, spell);

    if (settings.spellpoint_level_depend == TRUE) {
        if (spell->stats.sp && spell->stats.maxsp) {
            sp = (int)(spell->stats.sp*(1.0+MAX(0, (float)(level-spell->level)/(float)spell->stats.maxsp)));
        } else
            sp = spell->stats.sp;

        sp *= PATH_SP_MULT(caster, spell);
        if (!sp && spell->stats.sp)
            sp = 1;

        if (spell->stats.grace && spell->stats.maxgrace) {
            grace = (int)(spell->stats.grace*(1.0+MAX(0, (float)(level-spell->level)/(float)spell->stats.maxgrace)));
        } else
            grace = spell->stats.grace;

        grace *= PATH_SP_MULT(caster, spell);
        if (spell->stats.grace && !grace)
            grace = 1;
    } else {
        sp = spell->stats.sp*PATH_SP_MULT(caster, spell);
        if (spell->stats.sp && !sp)
            sp = 1;
        grace = spell->stats.grace*PATH_SP_MULT(caster, spell);
        if (spell->stats.grace && !grace)
            grace = 1;
    }
    if (flags == SPELL_HIGHEST)
        return MAX(sp, grace);
    else if (flags == SPELL_GRACE)
        return grace;
    else if (flags == SPELL_MANA)
        return sp;
    else {
        LOG(llevError, "SP_level_spellpoint_cost: Unknown flags passed: %d\n", flags);
        return 0;
    }
}
