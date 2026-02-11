ShowAchievementListHelper(AchievementEntry const* achEntry, LocaleConstant loc, time_t const* date , Player* target )
{
    std::string name = achEntry->name[loc];

    ObjectGuid guid = target ? target->GetObjectGuid() : ObjectGuid();


    std::ostringstream ss;
    if (m_session)
    {
        ss << achEntry->ID << " - |cffffffff|Hachievement:" << achEntry->ID << ":" << std::hex << guid.GetRawValue() << std::dec;
        if (date)
        {

            tm* aTm = localtime(date);
            ss << ":1:" << aTm->tm_mon + 1 << ":" << aTm->tm_mday << ":" << (aTm->tm_year + 1900 - 2000) << ":";


            ss << uint32(-1) << ":" << uint32(-1) << ":" << uint32(-1) << ":" << uint32(-1) << ":";
        }
        else
        {

            ss << ":0:0:0:-1:";


            if (target)
            {
                uint32 criteriaMask[4] = {0, 0, 0, 0};

                if (AchievementMgr const* mgr = target ? &target->GetAchievementMgr() : NULL)
                    if (AchievementCriteriaEntryList const* criteriaList = sAchievementMgr.GetAchievementCriteriaByAchievement(achEntry->ID))
                        for (AchievementCriteriaEntryList::const_iterator itr = criteriaList->begin(); itr != criteriaList->end(); ++itr)
                            if (mgr->IsCompletedCriteria(*itr, achEntry))
                                criteriaMask[((*itr)->showOrder - 1) / 32] |= (1 << (((*itr)->showOrder - 1) % 32));

                for (int i = 0; i < 4; ++i)
                    ss << criteriaMask[i] << ":";
            }
            else
                ss << "0:0:0:0:";
        }

        ss << "|h[" << name << " " << localeNames[loc] << "]|h|r";
    }
    else
        ss << achEntry->ID << " - " << name << " " << localeNames[loc];

    if (target && date)
        ss << " [" << TimeToTimestampStr(*date) << "]";

    SendSysMessage(ss.str().c_str());
}
