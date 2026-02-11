remove(const QString &name)
{
    if (!name.isEmpty())
    {
        ZoneMap::Iterator it = d->zones.find(name);
        if (it != d->zones.end())
        {
            KTimeZone zone = it.value();
            d->zones.erase(it);
            return zone;
        }
    }
    return KTimeZone();
}
