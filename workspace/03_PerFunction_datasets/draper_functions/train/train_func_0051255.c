AreaTrigger_at_ravenholdt(Player* pPlayer, AreaTriggerEntry const* )
{
    if (pPlayer->GetQuestStatus(QUEST_MANOR_RAVENHOLDT) == QUEST_STATUS_INCOMPLETE)
    {
        pPlayer->KilledMonsterCredit(NPC_RAVENHOLDT);
    }

    return false;
}
