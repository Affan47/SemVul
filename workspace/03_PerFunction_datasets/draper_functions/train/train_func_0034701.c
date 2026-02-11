tupleData( const TrackTuple &tuple, qint64 field, int role ) const
{
    ProviderPtr firstProvider = tuple.provider( 0 );
    TrackPtr first = tuple.track( firstProvider );
    switch( role )
    {
        case Qt::DisplayRole:
            switch( field )
            {
                case Meta::valTitle:
                    return trackTitleData( first );
                case Meta::valRating:
                    return tuple.syncedRating( m_options );
                case Meta::valFirstPlayed:
                    return tuple.syncedFirstPlayed( m_options );
                case Meta::valLastPlayed:
                    return tuple.syncedLastPlayed( m_options );
                case Meta::valPlaycount:
                    return tuple.syncedPlaycount( m_options );
                case Meta::valLabel:
                    if( tuple.fieldHasConflict( field, m_options,  false ) )
                        return -1;
                    return QStringList( tuple.syncedLabels( m_options ).toList() ).join(
                        i18nc( "comma between list words", ", " ) );
                default:
                    return QString( "Unknown field!" );
            }
            break;
        case Qt::ToolTipRole:
            switch( field )
            {
                case Meta::valTitle:
                    return trackToolTipData( first );
                case Meta::valLabel:
                    return QStringList( tuple.syncedLabels( m_options ).toList() ).join(
                        i18nc( "comma between list words", ", " ) );
            }
            break;
        case Qt::BackgroundRole:
            if( tuple.fieldUpdated( field, m_options ) )
                return KColorScheme( QPalette::Active ).background( KColorScheme::PositiveBackground );
            break;
        case Qt::TextAlignmentRole:
            return textAlignmentData( field );
        case Qt::SizeHintRole:
            return sizeHintData( field );
        case CommonModel::FieldRole:
            return field;
        case TupleFlagsRole:
            int flags = tuple.hasUpdate( m_options ) ? HasUpdate : 0;
            flags |= tuple.hasConflict( m_options ) ? HasConflict : 0;
            return flags;
    }
    return QVariant();
}
