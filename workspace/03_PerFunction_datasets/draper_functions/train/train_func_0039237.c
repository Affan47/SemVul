setData(const int ref, const QVariant &value, const QString &lang)
{
    QString l = lang.toLower();
    if (lang.isEmpty())
        l = Trans::Constants::ALL_LANGUAGE;

    if (value.canConvert(QVariant::DateTime)) {
        QDateTime dt = value.toDateTime();
        if (dt.time().msec() > 0) {
            dt = QDateTime(dt.date(), QTime(dt.time().hour(), dt.time().minute(), dt.time().second()));
            m_Data[l].insert(ref, dt);
        } else {
            m_Data[l].insert(ref, value);
        }
    } else {
        m_Data[l].insert(ref, value);
    }
    return true;
}
