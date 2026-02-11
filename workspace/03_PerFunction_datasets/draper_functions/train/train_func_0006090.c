ExtractSpellIdFromLink(char** text)
{


    int type;
    char* param1_str = NULL;
    char* idS = ExtractKeyFromLink(text, spellKeys, &type, &param1_str);
    if (!idS)
        { return 0; }

    uint32 id;
    if (!ExtractUInt32(&idS, id))
        { return 0; }

    switch (type)
    {
        case SPELL_LINK_RAW:
        case SPELL_LINK_SPELL:
        case SPELL_LINK_ENCHANT:
            return id;
        case SPELL_LINK_TALENT:
        {

            TalentEntry const* talentEntry = sTalentStore.LookupEntry(id);
            if (!talentEntry)
                { return 0; }

            int32 rank;
            if (!ExtractInt32(&param1_str, rank))
                { return 0; }

            if (rank < 0)
                { rank = 0; }

            return rank < MAX_TALENT_RANK ? talentEntry->RankID[rank] : 0;
        }
    }


    return 0;
}
