ai_count_df_units( Unit *unit, int x, int y, int *result )
{
    DefCtx ctx = { unit, 0 };
    *result = 0;
    if ( unit->sel_prop->flags & ARTILLERY )
        return;
    ai_eval_hexes( x, y, 3, hex_df_unit, &ctx );

    if ( *result > 3 )
        *result = 3;
}
