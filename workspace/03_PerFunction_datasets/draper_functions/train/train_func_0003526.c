findEntry(const char *name) const
{
    const DcmDictEntry* e = NULL;
    const DcmDictEntry* ePrivate = NULL;


    DcmHashDictIterator iter;
    for (iter = hashDict.begin(); (e == NULL) && (iter != hashDict.end()); ++iter) {
        if ((*iter)->contains(name)) {
            e = *iter;
            if (e->getGroup() % 2)
            {

                if (!ePrivate) ePrivate = e;
                e = NULL;
            }
        }
    }

    if (e == NULL) {

        OFBool found = OFFalse;
        DcmDictEntryListConstIterator iter2(repDict.begin());
        DcmDictEntryListConstIterator last(repDict.end());
        for (; !found && iter2 != last; ++iter2) {
            if ((*iter2)->contains(name)) {
                found = OFTrue;
                e = *iter2;
            }
        }
    }

    if (e == NULL && ePrivate != NULL) {

        e = ePrivate;
    }

    return e;
}
