EnterEvadeIfOutOfCombatArea(const uint32 uiDiff)
{
    if (m_uiEvadeCheckCooldown < uiDiff)
    {
        m_uiEvadeCheckCooldown = 2500;
    }
    else
    {
        m_uiEvadeCheckCooldown -= uiDiff;
        return false;
    }

    if (m_creature->IsInEvadeMode() || !m_creature->getVictim())
    {
        return false;
    }

    float fX = m_creature->GetPositionX();
    float fY = m_creature->GetPositionY();
    float fZ = m_creature->GetPositionZ();

    switch (m_creature->GetEntry())
    {
        case NPC_BROODLORD:
            if (fZ > 448.60f)
            {
                return false;
            }
            break;
        default:
            script_error_log("EnterEvadeIfOutOfCombatArea used for creature entry %u, but does not have any definition.", m_creature->GetEntry());
            return false;
    }

    EnterEvadeMode();
    return true;
}
