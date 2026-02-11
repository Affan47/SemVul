data( const QModelIndex &index, int role ) const
{
    if( !index.isValid() || index.column() != 0 ||
        index.row() < 0 || index.row() >= m_providers.count() )
    {
        return QVariant();
    }
    ProviderPtr provider = m_providers.at( index.row() );
    switch( role )
    {
        case Qt::DisplayRole:
            if( provider->description().isEmpty() )
                return provider->prettyName();
            return i18nc( "%1: name, %2: description", "%1 (%2)", provider->prettyName(),
                          provider->description() );
        case Qt::DecorationRole:
            return provider->icon();
        case Qt::ToolTipRole:
            return i18n( "Can match tracks by: %1\nCan synchronize: %2",
                         fieldsToString( provider->reliableTrackMetaData() ),
                         fieldsToString( provider->writableTrackStatsData() ) );
    }
    return QVariant();
}
