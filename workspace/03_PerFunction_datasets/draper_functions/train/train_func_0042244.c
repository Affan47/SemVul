GetMemberSlotWithdrawRem(uint32 LowGuid, uint8 TabId)
{
    MemberList::iterator itr = members.find(LowGuid);
    if (itr == members.end())
        return 0;

    if (itr->second.RankId == GR_GUILDMASTER)
        return WITHDRAW_SLOT_UNLIMITED;

    if ((GetBankRights(itr->second.RankId, TabId) & GUILD_BANK_RIGHT_VIEW_TAB) != GUILD_BANK_RIGHT_VIEW_TAB)
        return 0;

    uint32 curTime = uint32(time(NULL) / MINUTE);
    if (curTime - itr->second.BankResetTimeTab[TabId] >= 24 * HOUR / MINUTE)
    {
        itr->second.BankResetTimeTab[TabId] = curTime;
        itr->second.BankRemSlotsTab[TabId] = GetBankSlotPerDay(itr->second.RankId, TabId);
        CharacterDatabase.PExecute("UPDATE guild_member SET BankResetTimeTab%u='%u', BankRemSlotsTab%u='%u' WHERE guildid='%u' AND guid='%u'",
                                   uint32(TabId), itr->second.BankResetTimeTab[TabId], uint32(TabId), itr->second.BankRemSlotsTab[TabId], m_Id, LowGuid);
    }
    return itr->second.BankRemSlotsTab[TabId];
}
