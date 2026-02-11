getCEList(const UnicodeString *string) const
{
#ifdef CACHE_CELISTS
    return charsToCEList->get(string);
#else
    UErrorCode status = U_ZERO_ERROR;
    const CEList *list = new CEList(coll, *string, status);

    if (U_FAILURE(status)) {
        delete list;
        list = NULL;
    }

    return list;
#endif
}
