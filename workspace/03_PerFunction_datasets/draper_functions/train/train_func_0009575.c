HandleGuildBankDepositMoney(WorldPacket& recv_data)
{
    DEBUG_LOG("WORLD: Received (CMSG_GUILD_BANK_DEPOSIT_MONEY)");

    ObjectGuid goGuid;
    uint32 money;
    recv_data >> goGuid >> money;

    if (!money)
        return;

    if (!GetPlayer()->GetGameObjectIfCanInteractWith(goGuid, GAMEOBJECT_TYPE_GUILD_BANK))
        return;

    if (GetPlayer()->GetMoney() < money)
        return;

    uint32 GuildId = GetPlayer()->GetGuildId();
    if (!GuildId)
        return;

    Guild* pGuild = sGuildMgr.GetGuildById(GuildId);
    if (!pGuild)
        return;

    if (!pGuild->GetPurchasedTabs())
        return;

    CharacterDatabase.BeginTransaction();

    pGuild->SetBankMoney(pGuild->GetGuildBankMoney() + money);
    GetPlayer()->ModifyMoney(-int(money));
    GetPlayer()->SaveGoldToDB();

    CharacterDatabase.CommitTransaction();


    if (_player->GetSession()->GetSecurity() > SEC_PLAYER && sWorld.getConfig(CONFIG_BOOL_GM_LOG_TRADE))
    {
        sLog.outCommand(_player->GetSession()->GetAccountId(), "GM %s (Account: %u) deposit money (Amount: %u) to guild bank (Guild ID %u)",
                        _player->GetName(), _player->GetSession()->GetAccountId(), money, GuildId);
    }


    pGuild->LogBankEvent(GUILD_BANK_LOG_DEPOSIT_MONEY, uint8(0), GetPlayer()->GetGUIDLow(), money);

    pGuild->DisplayGuildBankTabsInfo(this);
    pGuild->DisplayGuildBankContent(this, 0);
    pGuild->DisplayGuildBankMoneyUpdate(this);
}
