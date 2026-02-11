removeSelected()
{
    DEBUG_BLOCK;

    QModelIndexList indexes = selectionModel()->selectedIndexes();

    if( indexes.isEmpty() )
        return;

    Dynamic::DynamicModel::instance()->removeAt( indexes.first() );
}
