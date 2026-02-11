newNameRec(name, hashvalue)
String name;
int hashvalue;
{
    CachedAtomNameRec *nrp = XtNew(CachedAtomNameRec);

    nrp->name = XtNewString(name);
    nrp->next = nameHash[hashvalue];
    nameHash[hashvalue] = nrp;
    return nrp;
}
