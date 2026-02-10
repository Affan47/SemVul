setSize(int x, int y)
{
    if (x == xTiles() && y == yTiles()) {
        return;
    }

    delete [] m_field;

    m_field = new int[ x * y ];
    m_xTiles = x;
    m_yTiles = y;
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            setField(i, j, EMPTY);
        }
    }


    const double MINIMUM_SCALE = 0.2;
    int w = qRound(m_tiles.qWidth() * 2.0 * MINIMUM_SCALE) * xTiles();
    int h = qRound(m_tiles.qHeight() * 2.0 * MINIMUM_SCALE) * yTiles();
    w += m_tiles.width();
    h += m_tiles.width();

    setMinimumSize(w, h);

    resizeBoard();
    newGame();
    emit changed();
}
