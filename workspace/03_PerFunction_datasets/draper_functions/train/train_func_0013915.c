matchesBlacklist(const QString &string) const
{
    if (!setSecondLevelDomain) {


        for (int j = 0; twoLevelDomains[j]; ++j)
            secondLevelDomains += QLatin1String(twoLevelDomains[j]);
        setSecondLevelDomain = true;
    }
    QStringList::const_iterator i =
         qBinaryFind(secondLevelDomains.constBegin(), secondLevelDomains.constEnd(), string);
        return (i != secondLevelDomains.constEnd());
}
