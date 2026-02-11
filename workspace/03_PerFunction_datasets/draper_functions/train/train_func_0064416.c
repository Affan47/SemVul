position_set_initial_partyend (Position *pos, int level)
{
	register Square square;
	register gshort rank;

	for (rank = 1; rank <= 8; rank++) {
		for (square = A1 + ((rank - 1) * 10);
		     square <= H1 + ((rank - 1) * 10);
		     square++) {
		pos->square [square] = EMPTY;
		}
	}

	switch(level) {
	case 1:
	default:

		pos->square [A1] = WK;
		pos->square [G1] = WQ;
		pos->square [F1] = WQ;


		pos->square [E8] = BK;


		pos->priv->wk_square = A1;
		pos->priv->bk_square = E8;
		break;
	case 2:

		pos->square [E1] = WK;
		pos->square [F1] = WR;
		pos->square [G1] = WR;


		pos->square [A8] = BK;


		pos->priv->wk_square = E1;
		pos->priv->bk_square = A8;
		break;
	case 3:

		pos->square [E1] = WK;
		pos->square [B4] = WR;
		pos->square [B5] = WB;


		pos->square [A1] = BK;


		pos->priv->wk_square = E1;
		pos->priv->bk_square = A1;
		break;
	}


	pos->priv->wr_a_move = 0;
	pos->priv->wr_h_move = 0;
	pos->priv->br_a_move = 0;
	pos->priv->br_h_move = 0;
	pos->priv->captured = EMPTY;
	pos->priv->tomove = WHITE;
}
