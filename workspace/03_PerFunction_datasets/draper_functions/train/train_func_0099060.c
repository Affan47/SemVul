formatHttpDate(qint64 date)
{
    KDateTime dt;
    dt.setTime_t(date);
    QString ret = dt.toString(KDateTime::RFCDateDay);
    ret.chop(6);

    if (!dt.time().second()) {
        ret.append(QLatin1String(":00"));
    }
    ret.append(QLatin1String(" GMT"));
    return ret;
}
