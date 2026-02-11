_LoadSpellCooldowns()
{
    m_CreatureSpellCooldowns.clear();
    m_CreatureCategoryCooldowns.clear();

    QueryResult* result = CharacterDatabase.PQuery("SELECT spell,time FROM pet_spell_cooldown WHERE guid = '%u'", m_charmInfo->GetPetNumber());

    if (result)
    {
        time_t curTime = time(NULL);

        WorldPacket data(SMSG_SPELL_COOLDOWN, (8 + size_t(result->GetRowCount()) * 8));
        data << ObjectGuid(GetObjectGuid());


        do
        {
            Field* fields = result->Fetch();

            uint32 spell_id = fields[0].GetUInt32();
            time_t db_time  = (time_t)fields[1].GetUInt64();

            if (!sSpellStore.LookupEntry(spell_id))
            {
                sLog.outError("Pet %u have unknown spell %u in `pet_spell_cooldown`, skipping.", m_charmInfo->GetPetNumber(), spell_id);
                continue;
            }


            if (db_time <= curTime)
                { continue; }

            data << uint32(spell_id);
            data << uint32(uint32(db_time - curTime)*IN_MILLISECONDS);

            _AddCreatureSpellCooldown(spell_id, db_time);

            DEBUG_LOG("Pet (Number: %u) spell %u cooldown loaded (%u secs).", m_charmInfo->GetPetNumber(), spell_id, uint32(db_time - curTime));
        }
        while (result->NextRow());

        delete result;

        if (!m_CreatureSpellCooldowns.empty() && GetOwner())
        {
            ((Player*)GetOwner())->GetSession()->SendPacket(&data);
        }
    }
}
