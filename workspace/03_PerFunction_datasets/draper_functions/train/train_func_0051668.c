EffectDummyCreature_summon_hakkar(Unit* pCaster, uint32 uiSpellId, SpellEffectIndex uiEffIndex, Creature* , ObjectGuid )
{

    if (uiSpellId == SPELL_SUMMON_AVATAR && uiEffIndex == EFFECT_INDEX_0)
    {
        if (!pCaster || pCaster->GetTypeId() != TYPEID_UNIT)
        {
            return true;
        }


        ((Creature*)pCaster)->UpdateEntry(NPC_AVATAR_OF_HAKKAR);
        pCaster->CastSpell(pCaster, SPELL_AVATAR_SUMMONED, true);
        DoScriptText(SAY_AVATAR_SPAWN, pCaster);


        return true;
    }

    return false;
}
