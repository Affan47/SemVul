knights_movegen (Pos *pos)
{
	int i, j, k;
	byte movbuf [64];
	byte *movlist, *movp = movbuf;
	Player player = pos->player;
	get_cur_pos (pos->board, player, &i, &j);
	for (k=0; k<8; k++)
	{
		int x = i + incx[k], y = j + incy[k];
		int val;
		if (!ISINBOARD (x, y)) continue;
		if ((val = pos->board[y * board_wid + x]) == KNIGHTS_EMPTY)
		{
			*movp++ = i;
			*movp++ = j;
			*movp++ = KNIGHTS_CLOSED;
			*movp++ = x;
			*movp++ = y;
			*movp++ = (player == WHITE ? KNIGHTS_WN : KNIGHTS_BN);
			*movp++ = -1;
		}
		else if (val == KNIGHTS_WN || val == KNIGHTS_BN)
		{
			*movp++ = -1;
		}
	}
	*movp++ = -2;
	movlist = (byte *) (malloc (movp - movbuf));
	memcpy (movlist, movbuf, (movp - movbuf));
	return movlist;
}
