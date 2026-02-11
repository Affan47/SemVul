SendGossipMenu(uint32 TitleTextId, ObjectGuid objectGuid)
{
    WorldPacket data(SMSG_GOSSIP_MESSAGE, (100));
    data << ObjectGuid(objectGuid);
    data << uint32(TitleTextId);
    data << uint32(mGossipMenu.MenuItemCount());

    for (uint32 iI = 0; iI < mGossipMenu.MenuItemCount(); ++iI)
    {
        GossipMenuItem const& gItem = mGossipMenu.GetItem(iI);
        data << uint32(iI);
        data << uint8(gItem.m_gIcon);
        data << uint8(gItem.m_gCoded);
        data << gItem.m_gMessage;
    }

    data << uint32(mQuestMenu.MenuItemCount());

    for (uint32 iI = 0; iI < mQuestMenu.MenuItemCount(); ++iI)
    {
        QuestMenuItem const& qItem = mQuestMenu.GetItem(iI);
        uint32 questID = qItem.m_qId;
        Quest const* pQuest = sObjectMgr.GetQuestTemplate(questID);

        data << uint32(questID);
        data << uint32(qItem.m_qIcon);
        data << int32(pQuest->GetQuestLevel());

        int loc_idx = GetMenuSession()->GetSessionDbLocaleIndex();
        std::string title = pQuest->GetTitle();
        sObjectMgr.GetQuestLocaleStrings(questID, loc_idx, &title);

        data << title;
    }

    GetMenuSession()->SendPacket(&data);
    DEBUG_LOG("WORLD: Sent SMSG_GOSSIP_MESSAGE from %s", objectGuid.GetString().c_str());
}
