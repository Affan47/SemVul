StartTimedAchievement(AchievementCriteriaTypes type, uint32 entry)
{
    for (BattleGroundPlayerMap::const_iterator itr = GetPlayers().begin(); itr != GetPlayers().end(); ++itr)
        if (Player* pPlayer = GetBgMap()->GetPlayer(itr->first))
            pPlayer->GetAchievementMgr().StartTimedAchievementCriteria(type, entry);
}
