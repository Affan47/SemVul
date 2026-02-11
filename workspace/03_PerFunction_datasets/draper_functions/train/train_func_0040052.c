RemoveAccessoriesFromMap()
{

    for (GuidSet::const_iterator itr = m_accessoryGuids.begin(); itr != m_accessoryGuids.end(); ++itr)
    {
        if (Creature* pAccessory = m_owner->GetMap()->GetCreature(*itr))
        {

            pAccessory->ForcedDespawn(5000);
        }
    }
    m_accessoryGuids.clear();
    m_isInitialized = false;
}
