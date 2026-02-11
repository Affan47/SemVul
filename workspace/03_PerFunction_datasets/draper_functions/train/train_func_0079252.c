state_see(state_t *state, int move)
{
    uint64_t attackers = util_attacks_to(state, MoveFrom(move)) & ~(1ull << MoveFrom(move));
    int attacked = eval_piece_values[MovePiece(move)];
    int color = Flip(state->turn);
    int ply = 1;
    int attacker;
    int swapstack[64];

    swapstack[0] = eval_real_pvalues[MoveCapture(move)];

    while (attackers)
    {
        uint64_t hits;
        for (attacker = PAWN; attacker <= KING; ++attacker)
        {
            hits = state->pieces[color][attacker] & attackers;
            if (hits)
            {
                break;
            }
        }

        if (attacker > KING)
            break;

        attackers ^= hits & -hits;
        swapstack[ply] = -swapstack[ply - 1] + attacked;
        attacked = eval_real_pvalues[attacker];
        color = Flip(color);
        ply += 1;
    }

    while (--ply)
        swapstack[ply - 1] = -Max(-swapstack[ply - 1], swapstack[ply]);

    return swapstack[0];
}
