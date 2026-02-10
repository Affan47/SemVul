castlingRightsString(FenNotation notation) const
{
	QString str;

	for (int side = Side::White; side <= Side::Black; side++)
	{
		for (int cside = KingSide; cside >= QueenSide; cside--)
		{
			int rs = m_castlingRights.rookSquare[side][cside];
			if (rs == 0)
				continue;

			int offset = (cside == QueenSide) ? -1: 1;
			Piece piece;
			int i = rs + offset;
			bool ambiguous = false;


			while (!(piece = pieceAt(i)).isWall())
			{
				if (piece == Piece(Side::Type(side), Rook))
				{
					ambiguous = true;
					break;
				}
				i += offset;
			}

			QChar c;


			if (ambiguous || notation == ShredderFen)
				c = QChar('a' + chessSquare(rs).file());
			else
			{
				if (cside == 0)
					c = 'q';
				else
					c = 'k';
			}
			if (side == upperCaseSide())
				c = c.toUpper();
			str += c;
		}
	}

	if (str.length() == 0)
		str = "-";
	return str;
}
