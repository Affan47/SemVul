CreateNewBankTab()
{
    if (GetPurchasedTabs() >= GUILD_BANK_MAX_TABS)
        return;

    uint32 tabId = GetPurchasedTabs();
    m_TabListMap.push_back(new GuildBankTab);

    CharacterDatabase.BeginTransaction();
    CharacterDatabase.PExecute("DELETE FROM guild_bank_tab WHERE guildid='%u' AND TabId='%u'", m_Id, tabId);
    CharacterDatabase.PExecute("INSERT INTO guild_bank_tab (guildid,TabId) VALUES ('%u','%u')", m_Id, tabId);
    CharacterDatabase.CommitTransaction();
}
