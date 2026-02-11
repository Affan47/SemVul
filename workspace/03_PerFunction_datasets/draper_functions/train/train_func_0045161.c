SetMonthlyQuestResetTime(bool initialize)
{
    if (initialize)
    {
        QueryResult* result = CharacterDatabase.Query("SELECT NextMonthlyQuestResetTime FROM saved_variables");

        if (!result)
            m_NextMonthlyQuestReset = time_t(time(NULL));
        else
            m_NextMonthlyQuestReset = time_t((*result)[0].GetUInt64());

        delete result;
    }


    time_t currentTime = time(NULL);
    tm localTm = *localtime(&currentTime);

    int month = localTm.tm_mon;
    int year = localTm.tm_year;

    ++month;


    if (month > 11)
    {
        month = 0;
        year += 1;
    }


    localTm.tm_year = year;
    localTm.tm_mon = month;
    localTm.tm_mday = 1;
    localTm.tm_hour = 0;
    localTm.tm_min  = 0;
    localTm.tm_sec  = 0;

    time_t nextMonthResetTime = mktime(&localTm);

    m_NextMonthlyQuestReset = (initialize && m_NextMonthlyQuestReset < nextMonthResetTime) ? m_NextMonthlyQuestReset : nextMonthResetTime;


    CharacterDatabase.PExecute("UPDATE saved_variables SET NextMonthlyQuestResetTime = '" UI64FMTD "'", uint64(m_NextMonthlyQuestReset));
}
