indexNeighbors()
{
    int offset = 0;
    for (int index = 0; index < m_nCubes; index++) {
        m_maxValues [index] = 0;
        for (int nb = 0; nb < 4; nb++) {
            m_neighbors [offset + nb] = -1;
        }

        int x = index / m_side;
        int y = index % m_side;
        int limit = m_side - 1;
        if (y > 0) {
            m_maxValues [index]++;
            m_neighbors [offset]     = index - 1;
        }
        if (y < limit) {
            m_maxValues [index]++;
            m_neighbors [offset + 1] = index + 1;
        }
        if (x < limit) {
            m_maxValues [index]++;
            m_neighbors [offset + 2] = index + m_side;
        }
        if (x > 0) {
            m_maxValues [index]++;
            m_neighbors [offset + 3] = index - m_side;
        }
	offset = offset + 4;
    }
}
