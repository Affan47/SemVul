checkUpdateLabel(const int index)
{
    switch (index) {
    case Constants::CheckUpdate_AtStartup: return tkTr(Constants::AT_STARTUP);

    case Constants::CheckUpdate_EachWeeks:return tkTr(Constants::EACH_WEEK);
    case Constants::CheckUpdate_EachMonth:return tkTr(Constants::EACH_MONTH);
    case Constants::CheckUpdate_EachQuarters:return tkTr(Constants::EACH_QUARTER);
    case Constants::CheckUpdate_Never:return tkTr(Constants::NEVER_AUTOMATICALLY);
    }
    return QString();
}
