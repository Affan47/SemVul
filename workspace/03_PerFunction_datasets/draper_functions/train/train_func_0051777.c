EffectDummyCreature_spell_capture_grark(Unit* , uint32 uiSpellId, SpellEffectIndex uiEffIndex, Creature* pCreatureTarget, ObjectGuid )
{

    if (uiSpellId == SPELL_CAPTURE_GRARK && uiEffIndex == EFFECT_INDEX_0)
    {

        if (pCreatureTarget->GetHealthPercent() > 25.0f)
        {
            return false;
        }


        DoScriptText(EMOTE_SUBMIT, pCreatureTarget);
        pCreatureTarget->SetFactionTemporary(FACTION_FRIENDLY, TEMPFACTION_RESTORE_RESPAWN);
        pCreatureTarget->AI()->EnterEvadeMode();


        return true;
    }

    return false;
}
