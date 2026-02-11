undrawConnection()
{
    if (m_tileRemove1.first != -1) {
        setField(m_tileRemove1.first, m_tileRemove1.second, EMPTY);
        setField(m_tileRemove2.first, m_tileRemove2.second, EMPTY);
        m_tileRemove1.first = -1;
        update();
    }

    gravity(true);


    if (m_connection.isEmpty()) {
        return;
    }


    Path oldConnection = m_connection;
    m_connection.clear();
    m_paintConnection = false;

    Path::const_iterator pt1 = oldConnection.constBegin();
    Path::const_iterator pt2 = pt1 + 1;
    while (pt2 != oldConnection.constEnd()) {
        if (pt1->y == pt2->y) {
            for (int i = qMin(pt1->x, pt2->x); i <= qMax(pt1->x, pt2->x); ++i) {
                updateField(i, pt1->y);
            }
        } else {
            for (int i = qMin(pt1->y, pt2->y); i <= qMax(pt1->y, pt2->y); ++i) {
                updateField(pt1->x, i);
            }
        }
        ++pt1;
        ++pt2;
    }

    PossibleMoves dummyPossibleMoves;

    if (!hint_I(dummyPossibleMoves)) {
        m_gameClock.pause();
        emit endOfGame();
    }
    m_paintInProgress = false;
}
