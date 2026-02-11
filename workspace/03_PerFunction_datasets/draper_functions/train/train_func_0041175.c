getMove()
{
    if (m_strategy.get() &&
        m_sea->turn() == m_player &&
        m_sea->status() == Sea::PLAYING) {
        Coord move = m_strategy->getMove();
        if ( move == Coord::invalid() ) {
            return desperateMove();
        }
        else {
            return move;
        }
    }
    else {
        return desperateMove();
    }
}
