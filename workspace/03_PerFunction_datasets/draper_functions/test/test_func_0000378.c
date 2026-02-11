insert_before(FWObject *o1, FWObject *obj)
{
    checkReadOnly();

    if (obj == NULL) return;
    if (o1 == NULL)
    {
        insert(begin(), obj);
        _adopt(obj);
        setDirty(true);
        return;
    }

    list<FWObject*>::iterator m = find(begin(), end(), o1);
    if (m != end())
    {
        insert(m, obj);
        _adopt(obj);
        setDirty(true);
    }
}
