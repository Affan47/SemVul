idl_id_is_in_idlist(IDList *idl, ID id)
{
    NIDS i;
    if (NULL == idl || NOID == id) {
        return 0;
    }
    if (ALLIDS(idl)) {
        return 1;
    }
    for (i = 0; i < idl->b_nids; i++) {
        if (id == idl->b_ids[i]) {
            return 1;
        }
    }
    return 0;
}
