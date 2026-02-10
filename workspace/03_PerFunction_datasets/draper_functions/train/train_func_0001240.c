SECITEM_DupArray(PLArenaPool *arena, const SECItemArray *from)
{
    SECItemArray *result;
    unsigned int i;


    if (!from || (!from->items && from->len))
        return NULL;

    result = SECITEM_AllocArray(arena, NULL, from->len);
    if (!result)
        return NULL;

    for (i = 0; i < from->len; ++i) {
        SECStatus rv = SECITEM_CopyItem(arena,
                                        &result->items[i], &from->items[i]);
        if (rv != SECSuccess) {
            SECITEM_ZfreeArray(result, PR_TRUE);
            return NULL;
        }
    }

    return result;
}
