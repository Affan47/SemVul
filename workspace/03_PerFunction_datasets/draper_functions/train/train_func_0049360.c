select( const QItemSelection & selection,
                                    QItemSelectionModel::SelectionFlags command )
{
    QList<QModelIndex> selections = selection.indexes();
    QList<QModelIndex>::ConstIterator it = selections.constBegin();
    for ( ; it != selections.constEnd(); ++it )
        if ( !( *it ).parent().isValid() )
            return QItemSelectionModel::select( selection, NoUpdate );

    QItemSelectionModel::select( selection, command );
}
