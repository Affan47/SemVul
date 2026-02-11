pawnMovesFrom(const Square s) const
{
    quint64 targets = bb_PawnF1[m_stm][s] & ~m_occupied;
    if(targets)
    {
        targets |= bb_PawnF2[m_stm][s] & ~m_occupied;
    }
    if(m_epSquare == NoEPSquare)
    {
        targets |= bb_PawnAttacks[m_stm][s] & m_occupied_co[m_stm ^ 1];
    }
    else
    {
        targets |= bb_PawnAttacks[m_stm][s] & (m_occupied_co[m_stm ^ 1] | SetBit(m_epSquare));
    }
    return targets;
}
