captureType(const Move& move) const
{
	Q_ASSERT(!move.isNull());

	Piece piece(m_squares.at(move.targetSquare()));
	if (piece.side() == m_side.opposite())
		return piece.type();
	return Piece::NoPiece;
}
