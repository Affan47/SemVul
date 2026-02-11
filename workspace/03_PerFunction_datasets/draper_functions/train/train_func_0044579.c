Delete(const String &key)
{
    DBT	k;

    memset(&k, 0, sizeof(DBT));

    if (!isOpen)
	return 0;

    k.data = (char*)key.get();
    k.size = key.length();

    return (dbp->del)(dbp, NULL, &k, 0);
}
