die()
{
    if(!m_death)
    {
        m_death = true;
        emit dying();
        m_xSpeed = 0;
        m_xSpeed = 0;

        if(m_badBonusCountdownTimer->isActive())
        {
            m_badBonusCountdownTimer->stop();
            slot_removeBadBonus();
        }
        int row = m_arena->getRowFromY(m_y);
        int column = m_arena->getColFromX(m_x);
        m_arena->removeCellElement(row, column, this);
    }
}
