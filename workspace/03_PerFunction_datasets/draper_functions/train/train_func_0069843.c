CompletedAchievement(AchievementEntry const* achievement)
{
    DETAIL_LOG("AchievementMgr::CompletedAchievement(%u)", achievement->ID);
    if (achievement->flags & ACHIEVEMENT_FLAG_COUNTER || m_completedAchievements.find(achievement->ID) != m_completedAchievements.end())
        return;

    SendAchievementEarned(achievement);
    CompletedAchievementData& ca =  m_completedAchievements[achievement->ID];
    ca.date = time(NULL);
    ca.changed = true;


    if (!(achievement->flags & ACHIEVEMENT_FLAG_REALM_FIRST_KILL))
        sAchievementMgr.SetRealmCompleted(achievement);

    UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_ACHIEVEMENT);


    AchievementReward const* reward = sAchievementMgr.GetAchievementReward(achievement, GetPlayer()->getGender());


    if (!reward)
        return;


    if (uint32 titleId = reward->titleId[GetPlayer()->GetTeam() == HORDE ? 1 : 0])
    {
        if (CharTitlesEntry const* titleEntry = sCharTitlesStore.LookupEntry(titleId))
            GetPlayer()->SetTitle(titleEntry);
    }


    if (reward->sender)
    {
        Item* item = reward->itemId ? Item::CreateItem(reward->itemId, 1, GetPlayer()) : NULL;

        int loc_idx = GetPlayer()->GetSession()->GetSessionDbLocaleIndex();


        std::string subject = reward->subject;
        std::string text = reward->text;
        if (loc_idx >= 0)
        {
            if (AchievementRewardLocale const* loc = sAchievementMgr.GetAchievementRewardLocale(achievement, GetPlayer()->getGender()))
            {
                if (loc->subject.size() > size_t(loc_idx) && !loc->subject[loc_idx].empty())
                    subject = loc->subject[loc_idx];
                if (loc->text.size() > size_t(loc_idx) && !loc->text[loc_idx].empty())
                    text = loc->text[loc_idx];
            }
        }

        MailDraft draft(subject, text);

        if (item)
        {

            item->SaveToDB();


            draft.AddItem(item);
        }

        draft.SendMailTo(GetPlayer(), MailSender(MAIL_CREATURE, reward->sender));
    }
}
