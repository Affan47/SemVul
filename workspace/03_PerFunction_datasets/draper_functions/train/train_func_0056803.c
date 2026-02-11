getMove()
    {

        if (!movesAvailable()) {
            kDebug() << "no moves available";
            setup();
        }
        for (int i = 0; i < 50; i++) {
            Coord c = getMoveHelper();

            if (m_sea->canHit(m_player, c)) {
                return c;
            }
        }

        return Coord::invalid();
    }
