Create(ObjectGuid guid, const char* name)
{
    m_leaderGuid = guid;
    m_leaderName = name;

    m_groupType  = isBGGroup() ? GROUPTYPE_BGRAID : GROUPTYPE_NORMAL;

    if (m_groupType & GROUPTYPE_RAID)
        _initRaidSubGroupsCounter();

    m_lootMethod = GROUP_LOOT;
    m_lootThreshold = ITEM_QUALITY_UNCOMMON;
    m_looterGuid = guid;

    m_dungeonDifficulty = DUNGEON_DIFFICULTY_NORMAL;
    m_raidDifficulty = RAID_DIFFICULTY_10MAN_NORMAL;
    if (!isBGGroup())
    {
        m_Id = sObjectMgr.GenerateGroupLowGuid();

        Player* leader = sObjectMgr.GetPlayer(guid);
        if (leader)
        {
            m_dungeonDifficulty = leader->GetDungeonDifficulty();
            m_raidDifficulty = leader->GetRaidDifficulty();
        }

        Player::ConvertInstancesToGroup(leader, this, guid);


        CharacterDatabase.BeginTransaction();
        CharacterDatabase.PExecute("DELETE FROM groups WHERE groupId ='%u'", m_Id);
        CharacterDatabase.PExecute("DELETE FROM group_member WHERE groupId ='%u'", m_Id);

        CharacterDatabase.PExecute("INSERT INTO groups (groupId,leaderGuid,mainTank,mainAssistant,lootMethod,looterGuid,lootThreshold,icon1,icon2,icon3,icon4,icon5,icon6,icon7,icon8,groupType,difficulty,raiddifficulty) "
                                   "VALUES ('%u','%u','%u','%u','%u','%u','%u','" UI64FMTD "','" UI64FMTD "','" UI64FMTD "','" UI64FMTD "','" UI64FMTD "','" UI64FMTD "','" UI64FMTD "','" UI64FMTD "','%u','%u','%u')",
                                   m_Id, m_leaderGuid.GetCounter(), m_mainTankGuid.GetCounter(), m_mainAssistantGuid.GetCounter(), uint32(m_lootMethod),
                                   m_looterGuid.GetCounter(), uint32(m_lootThreshold),
                                   m_targetIcons[0].GetRawValue(), m_targetIcons[1].GetRawValue(),
                                   m_targetIcons[2].GetRawValue(), m_targetIcons[3].GetRawValue(),
                                   m_targetIcons[4].GetRawValue(), m_targetIcons[5].GetRawValue(),
                                   m_targetIcons[6].GetRawValue(), m_targetIcons[7].GetRawValue(),
                                   uint8(m_groupType), uint32(m_dungeonDifficulty), uint32(m_raidDifficulty));
    }

    if (!AddMember(guid, name))
        return false;

    if (!isBGGroup())
        CharacterDatabase.CommitTransaction();

    return true;
}
