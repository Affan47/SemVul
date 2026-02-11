FillNotNormalLootFor(Player* pl)
{
    uint32 plguid = pl->GetGUIDLow();

    QuestItemMap::const_iterator qmapitr = m_playerQuestItems.find(plguid);
    if (qmapitr == m_playerQuestItems.end())
        FillQuestLoot(pl);

    qmapitr = m_playerFFAItems.find(plguid);
    if (qmapitr == m_playerFFAItems.end())
        FillFFALoot(pl);

    qmapitr = m_playerNonQuestNonFFAConditionalItems.find(plguid);
    if (qmapitr == m_playerNonQuestNonFFAConditionalItems.end())
        FillNonQuestNonFFAConditionalLoot(pl);
}
