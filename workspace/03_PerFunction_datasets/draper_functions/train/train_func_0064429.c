Ns_SetUniqueCmp(Ns_Set *set, char *key, int (*cmp) (char *s1, char *s2))
{
    int   i;
    char *name;
    int   found;

    found = 0;
    for (i = 0; i < set->size; ++i) {
        name = set->fields[i].name;
        if ((key == NULL && name == NULL) ||
            (key != NULL && name != NULL && ((*cmp) (key, name)) == 0)) {

            if (found) {
                return NS_FALSE;
            }
            found = 1;
        }
    }
    return NS_TRUE;
}
