StartTimedAchievementCriteria(AchievementCriteriaTypes type, uint32 timedRequirementId, time_t startTime )
{
    DETAIL_FILTER_LOG(LOG_FILTER_ACHIEVEMENT_UPDATES, "AchievementMgr::StartTimedAchievementCriteria(%u, %u)", type, timedRequirementId);

    if (!sWorld.getConfig(CONFIG_BOOL_GM_ALLOW_ACHIEVEMENT_GAINS) && m_player->GetSession()->GetSecurity() > SEC_PLAYER)
        return;

    AchievementCriteriaEntryList const& achievementCriteriaList = sAchievementMgr.GetAchievementCriteriaByType(type);
    for (AchievementCriteriaEntryList::const_iterator i = achievementCriteriaList.begin(); i != achievementCriteriaList.end(); ++i)
    {
        AchievementCriteriaEntry const* achievementCriteria = (*i);


        if (achievementCriteria->timedCriteriaMiscId != timedRequirementId)
            continue;

        if (!achievementCriteria->IsExplicitlyStartedTimedCriteria())
            continue;

        AchievementEntry const* achievement = sAchievementStore.LookupEntry(achievementCriteria->referredAchievement);


        if ((achievement->factionFlag == ACHIEVEMENT_FACTION_FLAG_HORDE    && GetPlayer()->GetTeam() != HORDE) ||
                (achievement->factionFlag == ACHIEVEMENT_FACTION_FLAG_ALLIANCE && GetPlayer()->GetTeam() != ALLIANCE))
            continue;


        if (IsCompletedCriteria(achievementCriteria, achievement))
            continue;


        if (achievementCriteria->requiredType == ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_QUEST && GetPlayer()->GetGroup())
            continue;


        if (startTime && time_t(startTime + achievementCriteria->timeLimit) < time(NULL))
            continue;

        CriteriaProgress* progress = NULL;

        CriteriaProgressMap::iterator iter = m_criteriaProgress.find(achievementCriteria->ID);
        if (iter == m_criteriaProgress.end())
            progress = &m_criteriaProgress[achievementCriteria->ID];
        else
            progress = &iter->second;

        progress->changed = true;
        progress->counter = 0;


        progress->date = startTime ? startTime : time(NULL);
        progress->timedCriteriaFailed = false;


        m_criteriaFailTimes[achievementCriteria->ID] = time_t(progress->date + achievementCriteria->timeLimit);

        SendCriteriaUpdate(achievementCriteria->ID, progress);
    }
}
