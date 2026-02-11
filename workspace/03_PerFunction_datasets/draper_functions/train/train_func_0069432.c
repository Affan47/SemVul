rowCount(const QModelIndex& index) const
{
    if ( action( index) ) {
        return 0;
    }
    ActionCollection* par = index.isValid() ? collection( index ) : d->collection.data();
    Q_ASSERT_X( par, "ActionCollectionModel::rowCount", "index is not an action nor a collection" );
    if (!par) {
        kWarning()<<"index is not an action nor a collection"<<index;
        return 0;
    }
    int rows = par->actions().count() + par->collections().count();
    return rows;
}
