writeXdgListEntry(const char *key, const QStringList &list, WriteConfigFlags flags)
{
    Q_ASSERT_X(isValid(), "KConfigGroup::writeXdgListEntry", "accessing an invalid group");
    Q_ASSERT_X(!d->bConst, "KConfigGroup::writeXdgListEntry", "writing to a read-only group");

    QString value;
    value.reserve(4096);


    QStringList::ConstIterator it = list.constBegin();
    const QStringList::ConstIterator end = list.constEnd();
    for (; it != end; ++it) {
        QString val(*it);
        val.replace(QLatin1Char('\\'), QLatin1String("\\\\")).replace(QLatin1Char(';'), QLatin1String("\\;"));
        value += val;
        value += QLatin1Char(';');
    }

    writeEntry(key, value, flags);
}
