dailySchemeXmlTagList()
{
    static QStringList tags;
    if (tags.count())
        return tags;
    tags
            << QString(Constants::WAKEUPTIME).remove(" ")
            << QString(Constants::BREAKFAST).remove(" ")
            << QString(Constants::MORNING).remove(" ")
            << QString(Constants::TENOCLOCKBRUNCH).remove(" ").remove("'")
            << QString(Constants::MIDDAY).remove(" ")
            << QString(Constants::LUNCH).remove(" ")
            << QString(Constants::TEATIME).remove(" ")
            << QString(Constants::EVENING).remove(" ")
            << QString(Constants::DINER).remove(" ")
            << QString(Constants::BEDTIME).remove(" ")
            ;
    return tags;
}
