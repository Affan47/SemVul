findInternedString(Object *string) {
    Object *interned;

    if(string == NULL)
        return NULL;


    findHashEntry(hash_table, string, interned, TRUE, FALSE, TRUE);

    return interned;
}
