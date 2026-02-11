LoadSpellLearnSpells()
{
    mSpellLearnSpells.clear();


    QueryResult* result = WorldDatabase.Query("SELECT entry, SpellID, Active FROM spell_learn_spell");
    if (!result)
    {
        BarGoLink bar(1);
        bar.step();

        sLog.outString();
        sLog.outString(">> Loaded 0 spell learn spells");
        sLog.outErrorDb("`spell_learn_spell` table is empty!");
        return;
    }

    uint32 count = 0;

    BarGoLink bar(result->GetRowCount());
    do
    {
        bar.step();
        Field* fields = result->Fetch();

        uint32 spell_id    = fields[0].GetUInt32();

        SpellLearnSpellNode node;
        node.spell      = fields[1].GetUInt32();
        node.active     = fields[2].GetBool();
        node.autoLearned = false;

        if (!sSpellStore.LookupEntry(spell_id))
        {
            sLog.outErrorDb("Spell %u listed in `spell_learn_spell` does not exist", spell_id);
            continue;
        }

        if (!sSpellStore.LookupEntry(node.spell))
        {
            sLog.outErrorDb("Spell %u listed in `spell_learn_spell` learning nonexistent spell %u", spell_id, node.spell);
            continue;
        }

        if (GetTalentSpellCost(node.spell))
        {
            sLog.outErrorDb("Spell %u listed in `spell_learn_spell` attempt learning talent spell %u, skipped", spell_id, node.spell);
            continue;
        }

        mSpellLearnSpells.insert(SpellLearnSpellMap::value_type(spell_id, node));

        ++count;
    }
    while (result->NextRow());

    delete result;


    uint32 dbc_count = 0;
    for (uint32 spell = 0; spell < sSpellStore.GetNumRows(); ++spell)
    {
        SpellEntry const* entry = sSpellStore.LookupEntry(spell);

        if (!entry)
            continue;

        for (int i = 0; i < MAX_EFFECT_INDEX; ++i)
        {
            if (entry->Effect[i] == SPELL_EFFECT_LEARN_SPELL)
            {
                SpellLearnSpellNode dbc_node;
                dbc_node.spell       = entry->EffectTriggerSpell[i];
                dbc_node.active      = true;


                if (!sSpellStore.LookupEntry(dbc_node.spell))
                    continue;


                dbc_node.autoLearned = entry->EffectImplicitTargetA[i] == TARGET_PET || GetTalentSpellCost(spell) > 0 || IsPassiveSpell(entry) || IsSpellHaveEffect(entry, SPELL_EFFECT_SKILL_STEP);

                SpellLearnSpellMapBounds db_node_bounds = GetSpellLearnSpellMapBounds(spell);

                bool found = false;
                for (SpellLearnSpellMap::const_iterator itr = db_node_bounds.first; itr != db_node_bounds.second; ++itr)
                {
                    if (itr->second.spell == dbc_node.spell)
                    {
                        sLog.outErrorDb("Spell %u auto-learn spell %u in spell.dbc then the record in `spell_learn_spell` is redundant, please fix DB.",
                                        spell, dbc_node.spell);
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    mSpellLearnSpells.insert(SpellLearnSpellMap::value_type(spell, dbc_node));
                    ++dbc_count;
                }
            }
        }
    }

    sLog.outString(">> Loaded %u spell learn spells + %u found in DBC", count, dbc_count);
    sLog.outString();
}
