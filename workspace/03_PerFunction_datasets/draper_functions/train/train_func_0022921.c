find_cached_dkey(struct derived_key *list, const krb5_data *constant)
{
    for (; list; list = list->next) {
        if (data_eq(list->constant, *constant)) {
            krb5_k_reference_key(NULL, list->dkey);
            return list->dkey;
        }
    }
    return NULL;
}
