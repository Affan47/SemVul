createVirtualUserCalendar(const QString &ownerUid, const QString &label, const QString &description,
                                           int defaultDurationInMinutes, int sortId,
                                           int type, int status, bool isDefault, bool isPrivate,
                                           const QString &password, const QString &iconPath,
                                           const QList<Calendar::People> &peoples)
{
    qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    QHash<int, QString> where;
    where.insert(CAL_LABEL, QString("='%1'").arg(label));
    where.insert(CAL_FULLCONTENT, QString("='%1'").arg(description));
    where.insert(CAL_DEFAULTDURATION, QString("=%1").arg(defaultDurationInMinutes));
    int alreadyInBase = count(Table_CALENDAR, CAL_ID, getWhereClause(Table_CALENDAR, where));
    if (alreadyInBase!=0) {
        LOG("Calendar is already in base, virtual user calendar not created");
        return 0;
    }
    UserCalendar *u = new UserCalendar;
    u->setData(UserCalendar::Uid, Utils::Database::createUid());
    u->setData(UserCalendar::UserOwnerUid, ownerUid);
    u->setData(UserCalendar::Label, label);
    u->setData(UserCalendar::Description, description);
    u->setData(UserCalendar::Type, type);
    u->setData(UserCalendar::Status, status);
    u->setData(UserCalendar::IsDefault, isDefault);
    u->setData(UserCalendar::IsPrivate, isPrivate);
    u->setData(UserCalendar::Password, password);
    u->setData(UserCalendar::AbsPathIcon, iconPath);
    u->setData(UserCalendar::DefaultDuration, defaultDurationInMinutes);
    u->setData(UserCalendar::SortId, sortId);
    u->setData(Constants::Db_IsVirtual, true);
    u->setData(Constants::Db_IsValid, true);
    u->setPeopleList(peoples);

    for(int i = 1; i < 6; ++i) {
        Agenda::DayAvailability av;
        av.setWeekDay(i);
        av.addTimeRange(QTime(7,0,0), QTime(20,0,0));
        u->addAvailabilities(av);
    }
    qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    if (!saveUserCalendar(u)) {
        delete u;
        u = 0;
    }
    qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    return u;
}
