unit_add_exp( Unit *unit, int exp )
{
    int old_level = unit->exp_level;
    unit->exp += exp;
    if ( unit->exp >= 500 ) unit->exp = 500;
    unit->exp_level = unit->exp / 100;
    return ( old_level != unit->exp_level );
}
