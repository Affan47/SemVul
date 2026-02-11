generateOpening()
{
	if (m_book[Chess::Side::White] == 0 || m_book[Chess::Side::Black] == 0)
		return;
	resetBoard();


	foreach (const Chess::Move& move, m_moves)
	{
		Q_ASSERT(m_board->isLegalMove(move));

		m_board->makeMove(move);
		if (!m_board->result().isNone())
			return;
	}


	forever
	{
		Chess::Move move = bookMove(m_board->sideToMove());
		if (move.isNull())
			break;

		m_board->makeMove(move);
		if (!m_board->result().isNone())
			break;

		m_moves.append(move);
	}
}
