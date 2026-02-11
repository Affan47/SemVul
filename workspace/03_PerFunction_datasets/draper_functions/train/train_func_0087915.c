readEntry(const char* key, const QStringList& aDefault) const
{
    Q_ASSERT_X(isValid(), "KConfigGroup::readEntry", "accessing an invalid group");

    const QString data = readEntry(key, QString());
    if (data.isNull())
        return aDefault;

    return KConfigGroupPrivate::deserializeList(data);
}
