FillInitialWorldStates(WorldPacket& data, uint32& count)
{
    FillInitialWorldState(data, count, m_zoneWorldState, WORLD_STATE_ADD);
    if (m_zoneWorldState == WORLD_STATE_TF_TOWERS_CONTROLLED)
    {
        FillInitialWorldState(data, count, WORLD_STATE_TF_TOWER_COUNT_H, m_towersHorde);
        FillInitialWorldState(data, count, WORLD_STATE_TF_TOWER_COUNT_A, m_towersAlliance);

        for (uint8 i = 0; i < MAX_TF_TOWERS; ++i)
            FillInitialWorldState(data, count, m_towerWorldState[i], WORLD_STATE_ADD);
    }
    else
        UpdateTimerWorldState();
}
