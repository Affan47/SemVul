SendConfirmLearn_npc_prof_blacksmith(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    if (uiAction)
    {
        uint32 eCreature = pCreature->GetEntry();
        switch (eCreature)
        {
            case 11191:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEARN_HAMMER, GOSSIP_SENDER_CHECK, uiAction);

                pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
                break;
            case 11192:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEARN_AXE,    GOSSIP_SENDER_CHECK, uiAction);

                pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
                break;
            case 11193:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEARN_SWORD,  GOSSIP_SENDER_CHECK, uiAction);

                pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
                break;
        }
    }
}
