SetCombatMovement(bool enable, bool stopOrStartMovement )
{
    m_isCombatMovement = enable;

    if (enable)
        m_creature->clearUnitState(UNIT_STAT_NO_COMBAT_MOVEMENT);
    else
        m_creature->addUnitState(UNIT_STAT_NO_COMBAT_MOVEMENT);

    if (stopOrStartMovement && m_creature->getVictim())
    {
        if (enable)
            m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim(), m_attackDistance, m_attackAngle);
        else if (!enable && m_creature->GetMotionMaster()->GetCurrentMovementGeneratorType() == CHASE_MOTION_TYPE)
            m_creature->StopMoving();
    }
}
