writableTrackStatsDataUnion() const
{
    qint64 fields = 0;
    foreach( const ProviderPtr &provider, selectedProviders() )
    {
        fields |= provider->writableTrackStatsData();
    }
    return fields;
}
