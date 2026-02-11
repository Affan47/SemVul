QuestAccept_npc_gilthares(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_FREE_FROM_HOLD)
    {
        pCreature->SetFactionTemporary(FACTION_ESCORT_H_NEUTRAL_ACTIVE, TEMPFACTION_RESTORE_RESPAWN);
        pCreature->SetStandState(UNIT_STAND_STATE_STAND);

        DoScriptText(SAY_GIL_START, pCreature, pPlayer);

        if (npc_giltharesAI* pEscortAI = dynamic_cast<npc_giltharesAI*>(pCreature->AI()))
        {
            pEscortAI->Start(false, pPlayer, pQuest);
        }
    }
    return true;
}
