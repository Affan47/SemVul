DoSortRoomEventMobs()
{
    if (GetData(TYPE_ROOM_EVENT) != NOT_STARTED)
    {
        return;
    }

    for (uint8 i = 0; i < MAX_ROOMS; ++i)
    {
        if (GameObject* pRune = instance->GetGameObject(m_aRoomRuneGuid[i]))
        {
            for (GuidList::const_iterator itr = m_lRoomEventMobGUIDList.begin(); itr != m_lRoomEventMobGUIDList.end(); ++itr)
            {
                Creature* pCreature = instance->GetCreature(*itr);
                if (pCreature && pCreature->IsAlive() && pCreature->GetDistance(pRune) < 10.0f)
                {
                    m_alRoomEventMobGUIDSorted[i].push_back(*itr);
                }
            }
        }
    }

    SetData(TYPE_ROOM_EVENT, IN_PROGRESS);
}
