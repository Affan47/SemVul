unmake_move(state_t *state, int move, int ply)
{
    uint64_t from_square, to_square;
    int from, to, piece, capture, promote;
    int opponent;
    uint64_t rook_mask;

    state->moves--;


    state->castling = state->old_castling[ply];
    state->en_passant = state->old_en_passant[ply];
    state->zobrist = state->old_zobrist[ply];
    state->last_pawn_or_cap = state->old_pawn_or_cap[ply];

    from = MoveFrom(move);
    to = MoveTo(move);
    piece = MovePiece(move);
    capture = MoveCapture(move);
    promote = MovePromote(move);

    from_square = 1ull << from;
    to_square = 1ull << to;
    opponent = state->turn;
    state->turn ^= 1;


    state->pieces[state->turn][piece] |= from_square;
    state->occupied[state->turn] |= from_square;
    state->square[from] = piece;

    state->occupied[state->turn] ^= to_square;
    state->square[to] = 7;

    if (promote < 6)
    {
        state->pieces[state->turn][promote] ^= to_square;
    }
    else
    {
        state->pieces[state->turn][piece] ^= to_square;
    }


    if (capture < 6)
    {
        uint64_t to_remove_square = to_square;
        if (piece == PAWN && to_square & state->en_passant)
        {


            to_remove_square = cached->moves_pawn_one[opponent][to];
        }


        state->pieces[opponent][capture] ^= to_remove_square;
        state->occupied[opponent] ^= to_remove_square;
        state->square[LSB(to_remove_square)] = capture;
    }

    switch (piece)
    {
        case PAWN:
        case KNIGHT:
        case BISHOP:
        case QUEEN:
            break;

        case KING:
            if (Abs(from - to) == 2)
            {
                rook_mask = cached->castling_rookmask[state->turn][from][to];
                state->pieces[state->turn][ROOK] ^= rook_mask;
                state->occupied[state->turn] ^= rook_mask;

                for (;rook_mask; ClearLow(rook_mask))
                {
                    int tmp = LSB(rook_mask);
                    state->square[tmp] = (state->square[tmp] == 7 ? ROOK : 7);
                }
            }

            state->king_idx[state->turn] = from;
            break;
    }

    state->occupied_both = state->occupied[WHITE] | state->occupied[BLACK];
}
