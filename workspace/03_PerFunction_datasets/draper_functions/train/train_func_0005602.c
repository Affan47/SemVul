DoResetKeeperEvent()
{
    if (m_lKeepers.empty())
    {
        script_error_log("Instance Uldaman: ERROR creature %u couldn't be found or something really bad happened.", NPC_STONE_KEEPER);
        return;
    }


    for (GuidList::const_iterator itr = m_lKeepers.begin(); itr != m_lKeepers.end(); ++itr)
    {
        if (Creature* pKeeper = instance->GetCreature(*itr))
        {
            if (!pKeeper->IsAlive())
            {
                pKeeper->Respawn();
            }
        }
    }
}
