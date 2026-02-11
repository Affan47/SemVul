EffectDummyCreature_npc_vault_warder(Unit* , uint32 uiSpellId, SpellEffectIndex uiEffIndex, Creature* pCreatureTarget, ObjectGuid )
{

    if (uiSpellId == SPELL_AWAKEN_VAULT_WARDER && uiEffIndex == EFFECT_INDEX_0)
    {
        if (pCreatureTarget->GetEntry() == NPC_VAULT_WARDER)
        {
            pCreatureTarget->RemoveAurasDueToSpell(SPELL_STONED);

            ScriptedInstance* pInstance = (ScriptedInstance*)pCreatureTarget->GetInstanceData();
            if (!pInstance)
            {
                return true;
            }

            if (Creature* pArchaedas = pInstance->GetSingleCreatureFromStorage(NPC_ARCHAEDAS))
            {
                pCreatureTarget->AI()->AttackStart(pArchaedas->getVictim());
            }

            return true;
        }
    }

    return false;
}
