CreatureRelocation(Creature* creature, float x, float y, float z, float ang)
{
    MANGOS_ASSERT(CheckGridIntegrity(creature, false));

    Cell old_cell = creature->GetCurrentCell();
    Cell new_cell(MaNGOS::ComputeCellPair(x, y));


    if (CreatureCellRelocation(creature, new_cell))
    {

        creature->Relocate(x, y, z, ang);
        creature->OnRelocated();
    }


    else if (!CreatureRespawnRelocation(creature))
    {

        DEBUG_FILTER_LOG(LOG_FILTER_CREATURE_MOVES, "Creature (GUID: %u Entry: %u ) can't be move to unloaded respawn grid.", creature->GetGUIDLow(), creature->GetEntry());
    }

    MANGOS_ASSERT(CheckGridIntegrity(creature, true));
}
