setCastlingSquare(Side side,
				     CastlingSide cside,
				     int square)
{
	int& rs = m_castlingRights.rookSquare[side][cside];
	if (rs == square)
		return;

	if (rs != 0)
		xorKey(m_zobrist->castling(side, rs));
	if (square != 0)
		xorKey(m_zobrist->castling(side, square));
	rs = square;
}
