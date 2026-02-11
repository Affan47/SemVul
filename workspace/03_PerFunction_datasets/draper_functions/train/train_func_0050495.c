filterAcceptsRow ( int source_row, const QModelIndex & source_parent ) const
{
    if( filterRegExp().isEmpty() ) return true;

    if( QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent) )
        return true;


    QModelIndex source_index = sourceModel()->index(source_row, 0, source_parent);
    for(int i = 0 ; i < sourceModel()->rowCount(source_index); i++) {
        if(filterAcceptsRow(i, source_index)) return true;
    }


    if(d_ptr->showAllChildren) {
        QModelIndex parent_index = source_parent;
        while(parent_index.isValid()) {
            int row = parent_index.row();
            parent_index = parent_index.parent();
            if(QSortFilterProxyModel::filterAcceptsRow(row, parent_index)) return true;
        }
    }

    return false;
}
