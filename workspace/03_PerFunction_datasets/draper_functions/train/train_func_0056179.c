HandleGossipSelectOption(Player* pPlayer, uint32 menuId, uint32 sender, uint32 action, std::string code)
{
    ENTRY_BEGIN(playerGossipBindings, menuId, GOSSIP_EVENT_ON_SELECT, return);
    pPlayer->PlayerTalkClass->ClearMenus();
    Push(L, pPlayer);
    Push(L, pPlayer);
    Push(L, sender);
    Push(L, action);
    if (code.empty())
        Push(L);
    else
        Push(L, code);
    ENTRY_EXECUTE(0);
    ENDCALL();
}
