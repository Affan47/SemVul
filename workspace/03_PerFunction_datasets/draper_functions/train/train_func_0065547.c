rowNumber( ActionCollection *collection ) const
{
    Q_ASSERT( collection != 0 );
    ActionCollection *par = collection->parentCollection();
    Q_ASSERT( par != 0 );
    int row = par->collections().indexOf( collection->objectName() ) + par->actions().count();
    return row;
}
