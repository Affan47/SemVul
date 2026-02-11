SetOneFactionReputation(FactionEntry const* factionEntry, int32 standing, bool incremental)
{
    FactionStateList::iterator itr = m_factions.find(factionEntry->reputationListID);
    if (itr != m_factions.end())
    {
        FactionState &faction = itr->second;
        int32 BaseRep = GetBaseReputation(factionEntry);

        if (incremental)
            standing += faction.Standing + BaseRep;

        if (standing > Reputation_Cap)
            standing = Reputation_Cap;
        else if (standing < Reputation_Bottom)
            standing = Reputation_Bottom;

        ReputationRank old_rank = ReputationToRank(faction.Standing + BaseRep);
        ReputationRank new_rank = ReputationToRank(standing);

        faction.Standing = standing - BaseRep;
        faction.needSend = true;
        faction.needSave = true;

        SetVisible(&faction);

        if (new_rank <= REP_HOSTILE)
            SetAtWar(&faction, true);

        UpdateRankCounters(old_rank, new_rank);

        m_player->ReputationChanged(factionEntry);

        AchievementMgr &achievementManager = m_player->GetAchievementMgr();
        achievementManager.UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_KNOWN_FACTIONS,         factionEntry->ID);
        achievementManager.UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_GAIN_REPUTATION,        factionEntry->ID);
        achievementManager.UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_GAIN_EXALTED_REPUTATION, factionEntry->ID);
        achievementManager.UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_GAIN_REVERED_REPUTATION, factionEntry->ID);
        achievementManager.UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_GAIN_HONORED_REPUTATION, factionEntry->ID);

        if (new_rank > old_rank)
            return true;
    }
    return false;
}
