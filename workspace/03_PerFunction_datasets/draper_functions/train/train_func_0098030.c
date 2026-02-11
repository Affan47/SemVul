items() const
{
    KCompletionMatchesWrapper list;
    bool addWeight = (d->myOrder == Weighted);
    extractStringsFromNode( d->myTreeRoot, QString(), &list, addWeight );

    return list.list();
}
