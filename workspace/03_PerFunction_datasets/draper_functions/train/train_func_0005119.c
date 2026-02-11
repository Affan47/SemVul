SetBankMoneyPerDay(uint32 rankId, uint32 money)
{
    if (rankId >= m_Ranks.size())
        return;

    if (rankId == GR_GUILDMASTER)
        money = WITHDRAW_MONEY_UNLIMITED;

    m_Ranks[rankId].BankMoneyPerDay = money;

    for (MemberList::iterator itr = members.begin(); itr != members.end(); ++itr)
    {
        MemberSlot &member = itr->second;
        if (member.RankId == rankId)
            member.BankResetTimeMoney = 0;
    }

    CharacterDatabase.PExecute("UPDATE guild_rank SET BankMoneyPerDay='%u' WHERE rid='%u' AND guildid='%u'", money, rankId, m_Id);
    CharacterDatabase.PExecute("UPDATE guild_member SET BankResetTimeMoney='0' WHERE guildid='%u' AND rank='%u'", m_Id, rankId);
}
