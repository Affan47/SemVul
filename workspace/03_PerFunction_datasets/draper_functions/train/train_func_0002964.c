LoadRewardLocales()
{
    m_achievementRewardLocales.clear();

    QueryResult* result = WorldDatabase.Query("SELECT entry,gender,subject_loc1,text_loc1,subject_loc2,text_loc2,subject_loc3,text_loc3,subject_loc4,text_loc4,subject_loc5,text_loc5,subject_loc6,text_loc6,subject_loc7,text_loc7,subject_loc8,text_loc8 FROM locales_achievement_reward");

    if (!result)
    {
        BarGoLink bar(1);

        bar.step();

        sLog.outString();
        sLog.outString(">> Loaded 0 achievement reward locale strings. DB table `locales_achievement_reward` is empty.");
        return;
    }

    BarGoLink bar(result->GetRowCount());

    do
    {
        Field* fields = result->Fetch();
        bar.step();

        uint32 entry = fields[0].GetUInt32();

        if (m_achievementRewards.find(entry) == m_achievementRewards.end())
        {
            sLog.outErrorDb("Table `locales_achievement_reward` (Entry: %u) has locale strings for nonexistent achievement reward .", entry);
            continue;
        }

        AchievementRewardLocale data;

        data.gender = Gender(fields[1].GetUInt8());

        if (data.gender >= MAX_GENDER)
            sLog.outErrorDb("Table `locales_achievement_reward` (Entry: %u) has wrong gender %u.", entry, data.gender);


        bool dup = false;
        AchievementRewardLocalesMapBounds bounds = m_achievementRewardLocales.equal_range(entry);
        for (AchievementRewardLocalesMap::const_iterator iter = bounds.first; iter != bounds.second; ++iter)
        {
            if (iter->second.gender == GENDER_NONE || data.gender == GENDER_NONE)
            {
                dup = true;
                sLog.outErrorDb("Table `locales_achievement_reward` must have single GENDER_NONE (%u) case (Entry: %u), ignore duplicate case", GENDER_NONE, entry);
                break;
            }
        }
        if (dup)
            continue;

        for (int i = 1; i < MAX_LOCALE; ++i)
        {
            std::string str = fields[2 + 2 * (i - 1)].GetCppString();
            if (!str.empty())
            {
                int idx = sObjectMgr.GetOrNewIndexForLocale(LocaleConstant(i));
                if (idx >= 0)
                {
                    if (data.subject.size() <= size_t(idx))
                        data.subject.resize(idx + 1);

                    data.subject[idx] = str;
                }
            }
            str = fields[2 + 2 * (i - 1) + 1].GetCppString();
            if (!str.empty())
            {
                int idx = sObjectMgr.GetOrNewIndexForLocale(LocaleConstant(i));
                if (idx >= 0)
                {
                    if (data.text.size() <= size_t(idx))
                        data.text.resize(idx + 1);

                    data.text[idx] = str;
                }
            }
        }

        m_achievementRewardLocales.insert(AchievementRewardLocalesMap::value_type(entry, data));
    }
    while (result->NextRow());

    delete result;

    sLog.outString();
    sLog.outString(">> Loaded " SIZEFMTD " achievement reward locale strings", m_achievementRewardLocales.size());
}
