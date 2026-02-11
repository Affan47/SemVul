cmark_match_rollout(listOLD * match)
{
    listOLD *pl;

    for (pl = match->plNext; pl != match; pl = pl->plNext) {
        if (cmark_game_rollout(pl->p) < 0)
            break;
    }
}
