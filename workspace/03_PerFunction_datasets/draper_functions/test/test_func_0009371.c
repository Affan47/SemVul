Put(const String &key, const String &data)
{
    DBT	k, d;

    memset(&k, 0, sizeof(DBT));
    memset(&d, 0, sizeof(DBT));

    if (!isOpen)
	return NOTOK;

    k.data = (char*)key.get();
    k.size = key.length();

    d.data = (char*)data.get();
    d.size = data.length();


    return (dbp->put)(dbp, NULL, &k, &d, 0) == 0 ? OK : NOTOK;
}
