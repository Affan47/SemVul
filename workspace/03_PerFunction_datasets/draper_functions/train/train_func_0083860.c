makeMove(const KReversiMove &move)
{
    if (!move.isValid()) {
        kickCurrentPlayer();
        return;
    }

    if (move.color != m_curPlayer)
        return;

    if (!isMovePossible(move)) {
        kickCurrentPlayer();
        return;
    }

    m_lastPlayer = m_curPlayer;
    m_curPlayer = NoColor;

    turnChips(move);

    m_delayTimer.singleShot(m_delay * (qMax(1, m_changedChips.count() - 1)), this, SLOT(onDelayTimer()));
    emit boardChanged();
}
