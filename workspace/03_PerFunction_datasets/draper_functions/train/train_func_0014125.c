interpreterInfo(const QString& interpretername) const
{
    return hasInterpreterInfo(interpretername) ? d->interpreterinfos[interpretername] : 0;
}
