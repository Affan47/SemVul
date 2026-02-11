lanMoveString(const Move& move)
{
	QString str;


	if (move.sourceSquare() == 0)
	{
		Q_ASSERT(move.promotion() != Piece::NoPiece);
		str += pieceSymbol(move.promotion()).toUpper() + '@';
		str += squareString(move.targetSquare());
		return str;
	}

	str += squareString(move.sourceSquare());
	str += squareString(move.targetSquare());
	if (move.promotion() != Piece::NoPiece)
		str += pieceSymbol(move.promotion()).toLower();

	return str;
}
