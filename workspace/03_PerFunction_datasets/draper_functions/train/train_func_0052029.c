EffectDummyCreature_spell_banner_of_provocation(Unit* , uint32 uiSpellId, SpellEffectIndex uiEffIndex, Creature* pCreatureTarget, ObjectGuid )
{
    if (uiSpellId == SPELL_SUMMON_THELRIN_DND && uiEffIndex != EFFECT_INDEX_0)
    {
        instance_blackrock_depths* pInstance = (instance_blackrock_depths*)pCreatureTarget->GetInstanceData();
        if (pInstance && pInstance->GetData(TYPE_RING_OF_LAW) != DONE && pInstance->GetData(TYPE_RING_OF_LAW) != SPECIAL)
        {
            pInstance->SetData(TYPE_RING_OF_LAW, pInstance->GetData(TYPE_RING_OF_LAW) == IN_PROGRESS ? uint32(SPECIAL) : uint32(DATA_BANNER_BEFORE_EVENT));
        }

        return true;
    }
    return false;
}
