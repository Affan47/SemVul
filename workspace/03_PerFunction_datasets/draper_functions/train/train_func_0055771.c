UpdateMotion(uint32 diff)
{
    if (m_owner->hasUnitState(UNIT_STAT_CAN_NOT_MOVE))
        { return; }

    MANGOS_ASSERT(!empty());
    m_cleanFlag |= MMCF_UPDATE;

    if (!top()->Update(*m_owner, diff))
    {
        m_cleanFlag &= ~MMCF_UPDATE;
        MovementExpired();
    }
    else
        { m_cleanFlag &= ~MMCF_UPDATE; }

    if (m_expList)
    {
        for (size_t i = 0; i < m_expList->size(); ++i)
        {
            MovementGenerator* mg = (*m_expList)[i];
            if (!isStatic(mg))
                { delete mg; }
        }

        delete m_expList;
        m_expList = NULL;

        if (empty())
            { Initialize(); }

        if (m_cleanFlag & MMCF_RESET)
        {
            top()->Reset(*m_owner);
            m_cleanFlag &= ~MMCF_RESET;
        }
    }
}
