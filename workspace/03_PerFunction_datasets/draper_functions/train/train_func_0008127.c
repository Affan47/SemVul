vFenString(FenNotation notation) const
{

	QString fen = castlingRightsString(notation) + ' ';


	if (m_enpassantSquare != 0)
		fen += squareString(m_enpassantSquare);
	else
		fen += '-';


	fen += ' ';
	fen += QString::number(m_reversibleMoveCount);


	fen += ' ';
	fen += QString::number(m_history.size() / 2 + 1);

	return fen;
}
