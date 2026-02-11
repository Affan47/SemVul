mtpe_next_position(TermDocEnum *tde)
{
    CHECK_CURR_TDE("next_position");
    return MTDE(tde)->curr_tde->next_position(MTDE(tde)->curr_tde);
}
