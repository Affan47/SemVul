EffectDummyCreature_npc_aged_dying_ancient_kodo(Unit* pCaster, uint32 spellId, SpellEffectIndex effIndex, Creature* pCreatureTarget, ObjectGuid )
{

    if (spellId == SPELL_KODO_KOMBO_ITEM && effIndex == EFFECT_INDEX_0)
    {

        if (pCaster->HasAura(SPELL_KODO_KOMBO_PLAYER_BUFF) || pCreatureTarget->HasAura(SPELL_KODO_KOMBO_DESPAWN_BUFF))
        {
            return true;
        }

        if (pCreatureTarget->GetEntry() == NPC_AGED_KODO ||
            pCreatureTarget->GetEntry() == NPC_DYING_KODO ||
            pCreatureTarget->GetEntry() == NPC_ANCIENT_KODO)
        {
            pCaster->CastSpell(pCaster, SPELL_KODO_KOMBO_PLAYER_BUFF, true);

            pCreatureTarget->UpdateEntry(NPC_TAMED_KODO);
            pCreatureTarget->CastSpell(pCreatureTarget, SPELL_KODO_KOMBO_DESPAWN_BUFF, false);

            if (pCreatureTarget->GetMotionMaster()->GetCurrentMovementGeneratorType() == WAYPOINT_MOTION_TYPE)
            {
                pCreatureTarget->GetMotionMaster()->MoveIdle();
            }

            pCreatureTarget->GetMotionMaster()->MoveFollow(pCaster, PET_FOLLOW_DIST, PET_FOLLOW_ANGLE);
        }


        return true;
    }
    return false;
}
