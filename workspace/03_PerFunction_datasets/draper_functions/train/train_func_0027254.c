AreaTrigger_at_twiggy_flathead(Player* pPlayer, AreaTriggerEntry const* )
{
    if (pPlayer->IsAlive() && !pPlayer->isGameMaster() && pPlayer->GetQuestStatus(QUEST_AFFRAY) == QUEST_STATUS_INCOMPLETE)
    {
        Creature* pCreature = GetClosestCreatureWithEntry(pPlayer, NPC_TWIGGY, 30.0f);
        if (!pCreature)
        {
            return true;
        }

        if (npc_twiggy_flatheadAI* pTwiggyAI = dynamic_cast<npc_twiggy_flatheadAI*>(pCreature->AI()))
        {
            if (pTwiggyAI->CanStartEvent(pPlayer))
            {
                return false;
            }
        }

        return true;
    }
    return true;
}
