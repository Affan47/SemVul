init_masks()
{
	for (Square sq=A1; sq<=H8; sq++) {
		int r, f;


		passed_pawn_mask[WHITE][sq] = NULLBITBOARD;
		for (r=RNK(sq)+1; r<=7; r++) {
			f = FIL(sq);

			passed_pawn_mask[WHITE][sq].setbit(SQUARE(r, f));
			if (f > 0) {
				passed_pawn_mask[WHITE][sq]
					.setbit(SQUARE(r, f-1));
			}
			if (f < 7) {
				passed_pawn_mask[WHITE][sq]
					.setbit(SQUARE(r, f+1));
			}
		}


		passed_pawn_mask[BLACK][sq] = NULLBITBOARD;
		for (r=RNK(sq)-1; r>=0; r--) {
			f = FIL(sq);

			passed_pawn_mask[BLACK][sq].setbit(SQUARE(r, f));
			if (f > 0) {
				passed_pawn_mask[BLACK][sq]
					.setbit(SQUARE(r, f-1));
			}
			if (f < 7) {
				passed_pawn_mask[BLACK][sq]
					.setbit(SQUARE(r, f+1));
			}
		}


		f = FIL(sq);
		isolated_pawn_mask[sq] = file[f];
		if (f > 0) {
			isolated_pawn_mask[sq] |= file[f-1];
		}
		if (f < 7) {
			isolated_pawn_mask[sq] |= file[f+1];
		}


		connected_pawn_mask[sq] = attack_bb[KING][sq]
			& ~file[FIL(sq)];
	}
}
