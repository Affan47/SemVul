flags( const QModelIndex &idx ) const
{


    if( idx.column() == PlaylistBrowserModel::ProviderColumn )
        return Qt::ItemIsEnabled | Qt::ItemIsEditable;

    if( idx.column() == PlaylistBrowserModel::LabelColumn )
        return Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsDropEnabled;

    if( !idx.isValid() )
        return Qt::ItemIsDropEnabled;

    if( IS_TRACK(idx) )
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled;


    return Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled |
           Qt::ItemIsDropEnabled;
}
