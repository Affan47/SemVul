AddToBGFreeSlotQueue()
{

    if (!m_InBGFreeSlotQueue && isBattleGround())
    {
        sBattleGroundMgr.BGFreeSlotQueue[m_TypeID].push_front(this);
        m_InBGFreeSlotQueue = true;
    }
}
