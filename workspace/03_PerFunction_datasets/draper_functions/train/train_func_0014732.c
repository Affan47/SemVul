moveToBits(const Chess::GenericMove& move)
{
	using Chess::Square;

	const Square& src = move.sourceSquare();
	const Square& trg = move.targetSquare();

	quint16 target = trg.file() | (trg.rank() << 3);
	quint16 source = (src.file() << 6) | (src.rank() << 9);
	quint16 promotion = 0;
	if (move.promotion() > 0)
		promotion = (move.promotion() - 1) << 12;

	return target | source | promotion;
}
