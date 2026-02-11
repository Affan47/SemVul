GossipHello_npc_disciple_of_naralex(Player* pPlayer, Creature* pCreature)
{
    ScriptedInstance* m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();

    if (pCreature->IsQuestGiver())
    {
        pPlayer->PrepareQuestMenu(pCreature->GetObjectGuid());
    }


    pCreature->CastSpell(pPlayer, SPELL_MARK, false);

    if (m_pInstance && m_pInstance->GetData(TYPE_DISCIPLE) == SPECIAL)
    {
        pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_ITEM_BEGIN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        pPlayer->SEND_GOSSIP_MENU(TEXT_ID_DISCIPLE, pCreature->GetObjectGuid());
    }
    else
    {
        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
    }

    return true;
}
