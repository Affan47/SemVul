headerData( int section, Qt::Orientation orientation, int role ) const
{
    Q_UNUSED( orientation );

    if ( role != Qt::DisplayRole )
        return QVariant();

    return columnName( static_cast<Playlist::Column>( section ) );
}
