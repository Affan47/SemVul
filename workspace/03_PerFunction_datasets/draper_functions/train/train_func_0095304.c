SendMineWorldStates(uint32 mine)
{
    MANGOS_ASSERT(mine == BG_AV_NORTH_MINE || mine == BG_AV_SOUTH_MINE);

    UpdateWorldState(BG_AV_MineWorldStates[mine][m_Mine_Owner[mine]], WORLD_STATE_ADD);
    if (m_Mine_Owner[mine] != m_Mine_PrevOwner[mine])
        { UpdateWorldState(BG_AV_MineWorldStates[mine][m_Mine_PrevOwner[mine]], WORLD_STATE_REMOVE); }
}
