toHumanFen() const
{
    QString fenFormat = QCoreApplication::translate("BitBoard", "w%1\nb%2\n%3 to move.");
    QMap<Piece, QStringList> charLists;


    for(int row = 7; row >= 0; row--)
    {
        for(int col = 0; col < 8; ++col)
        {
            Piece piece = pieceAt(8 * row + col);
            if(piece != Empty)
            {
                charLists[piece].append(QString("%1%2").arg(QChar('a' + col)).arg(row + 1));
            }
        }
    }


    QString toMove = (m_stm == White) ? QCoreApplication::translate("BitBoard", "White") : QCoreApplication::translate("BitBoard", "Black");

    QString w, b;
    for(Piece p = WhiteKing; p <= WhitePawn; ++p)
    {
        if(charLists.keys().contains(p))
        {
            if(!w.isEmpty())
            {
                w += ",";
            }
            w.append(pieceToHumanChar(p));
            w.append(charLists[p].join(","));
        }
    }
    for(Piece p = BlackKing; p != Empty; ++p)
    {
        if(charLists.keys().contains(p))
        {
            if(!b.isEmpty())
            {
                b += ",";
            }
            b.append(pieceToHumanChar(p));
            b.append(charLists[p].join(","));
        }
    }

    QString fen = fenFormat.arg(w).arg(b).arg(toMove);

    return fen;
}
