lockPhases()
{
    if (m_active != m_units.end() && (*m_active)->isMoving()) {
        if ((*m_active)->isPushing()) {
            m_speedup = 0;
        }
        else if (!(*m_active)->isTurning()) {
            m_speedup++;
        }

        m_locker->ensurePhases(getNeededPhases(m_speedup));
    }
    else {
        m_speedup = 0;
    }
}
