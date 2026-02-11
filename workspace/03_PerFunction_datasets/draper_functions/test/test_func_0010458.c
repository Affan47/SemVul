GossipHello_boss_vaelastrasz(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->IsQuestGiver())
    {
        pPlayer->PrepareQuestMenu(pCreature->GetObjectGuid());
    }

    pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_ITEM_VAEL_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXT_VAEL_1, pCreature->GetObjectGuid());

    return true;
}
