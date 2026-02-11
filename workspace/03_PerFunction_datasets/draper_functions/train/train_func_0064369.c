MovementInform(uint32 uiMoveType, uint32 uiPointId)
{
    if (uiMoveType != POINT_MOTION_TYPE || !HasEscortState(STATE_ESCORT_ESCORTING))
    {
        return;
    }


    if (uiPointId == POINT_LAST_POINT)
    {
        debug_log("SD2: EscortAI has returned to original position before combat");

        m_creature->SetWalk(!m_bIsRunning);
        RemoveEscortState(STATE_ESCORT_RETURNING);
    }
    else if (uiPointId == POINT_HOME)
    {
        debug_log("SD2: EscortAI has returned to original home location and will continue from beginning of waypoint list.");

        CurrentWP = WaypointList.begin();
        m_uiWPWaitTimer = 0;
    }
    else
    {

        if (CurrentWP->uiId != uiPointId)
        {
            script_error_log("EscortAI for Npc %u reached waypoint out of order %u, expected %u.", m_creature->GetEntry(), uiPointId, CurrentWP->uiId);
            return;
        }

        debug_log("SD2: EscortAI waypoint %u reached.", CurrentWP->uiId);


        m_creature->SetCombatStartPosition(m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ());


        WaypointReached(CurrentWP->uiId);

        m_uiWPWaitTimer = CurrentWP->uiWaitTime;

        ++CurrentWP;
    }

    if (!m_uiWPWaitTimer)
    {

        if (HasEscortState(STATE_ESCORT_ESCORTING) && !HasEscortState(STATE_ESCORT_PAUSED | STATE_ESCORT_RETURNING) && !m_creature->getVictim())
        {
            MoveToNextWaypoint();
        }
        else
        {
            m_uiWPWaitTimer = 1;
        }
    }
}
