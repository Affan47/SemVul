Update(uint32 uiDiff)
{
    if (GetData(TYPE_RAJAXX) == IN_PROGRESS)
    {
        if (m_uiArmyDelayTimer)
        {
            if (m_uiArmyDelayTimer <= uiDiff)
            {
                DoSendNextArmyWave();
                m_uiArmyDelayTimer = 2 * MINUTE * IN_MILLISECONDS;
            }
            else
            {
                m_uiArmyDelayTimer -= uiDiff;
            }
        }
    }
}
