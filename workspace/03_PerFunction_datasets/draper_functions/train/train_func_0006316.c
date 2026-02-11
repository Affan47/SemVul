LoadSkillExtraItemTable()
{
    uint32 count = 0;

    SkillExtraItemStore.clear();


    QueryResult* result = WorldDatabase.Query("SELECT spellId, requiredSpecialization, additionalCreateChance, additionalMaxNum FROM skill_extra_item_template");

    if (result)
    {
        BarGoLink bar(result->GetRowCount());

        do
        {
            Field* fields = result->Fetch();
            bar.step();

            uint32 spellId = fields[0].GetUInt32();

            if (!sSpellStore.LookupEntry(spellId))
            {
                sLog.outError("Skill specialization %u has nonexistent spell id in `skill_extra_item_template`!", spellId);
                continue;
            }

            uint32 requiredSpecialization = fields[1].GetUInt32();
            if (!sSpellStore.LookupEntry(requiredSpecialization))
            {
                sLog.outError("Skill specialization %u have nonexistent required specialization spell id %u in `skill_extra_item_template`!", spellId, requiredSpecialization);
                continue;
            }

            float additionalCreateChance = fields[2].GetFloat();
            if (additionalCreateChance <= 0.0f)
            {
                sLog.outError("Skill specialization %u has too low additional create chance in `skill_extra_item_template`!", spellId);
                continue;
            }

            uint8 additionalMaxNum = fields[3].GetUInt8();
            if (!additionalMaxNum)
            {
                sLog.outError("Skill specialization %u has 0 max number of extra items in `skill_extra_item_template`!", spellId);
                continue;
            }

            SkillExtraItemEntry& skillExtraItemEntry = SkillExtraItemStore[spellId];

            skillExtraItemEntry.requiredSpecialization = requiredSpecialization;
            skillExtraItemEntry.additionalCreateChance = additionalCreateChance;
            skillExtraItemEntry.additionalMaxNum       = additionalMaxNum;

            ++count;
        }
        while (result->NextRow());

        delete result;

        sLog.outString();
        sLog.outString(">> Loaded %u spell specialization definitions", count);
    }
    else
    {
        sLog.outString();
        sLog.outString(">> Loaded 0 spell specialization definitions. DB table `skill_extra_item_template` is empty.");
    }
}
