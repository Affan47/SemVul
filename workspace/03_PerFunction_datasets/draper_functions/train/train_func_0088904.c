idl_insert(IDList **idl, ID id)
{
    ID	i, j;
    NIDS  nids;

    if ((*idl) == NULL) {
        (*idl) = idl_alloc(1);
        idl_append((*idl), id);
        return;
    }

    if (ALLIDS(*idl)) {
        return;
    }

    i = nids = (*idl)->b_nids;

    if (nids > 0) {

        if (id == (*idl)->b_ids[nids-1]) {
            return;
        } else if (id > (*idl)->b_ids[nids-1]) {
            if (nids < (*idl)->b_nmax) {
                (*idl)->b_ids[nids] = id;
                (*idl)->b_nids++;
                return;
            }

            i = nids;

        } else if (id < (*idl)->b_ids[0]) {

            i = 0;
        } else {
            int lo = 0;
            int hi = (*idl)->b_nids - 1;
            int mid = 0;
            ID *ids = (*idl)->b_ids;

            if (0 != (*idl)->b_nids) {
                while (lo <= hi) {
                    mid = (hi + lo) >> 1;
                    if (ids[mid] > id) {
                        hi = mid - 1;
                    } else {
                        if (ids[mid] < id) {
                            lo = mid + 1;
                        } else {

                            return;
                        }
                    }
                }
            }
            i = lo;
        }
    }


    if ( (*idl)->b_nids == (*idl)->b_nmax ) {
        (*idl)->b_nmax *= 2;

        (*idl) = (IDList *) slapi_ch_realloc( (char *) (*idl),
                                            ((*idl)->b_nmax + 2) * sizeof(ID) + sizeof(IDList) );
    }


    for ( j = (*idl)->b_nids; j != i; j-- ) {
        (*idl)->b_ids[j] = (*idl)->b_ids[j-1];
    }

    (*idl)->b_ids[i] = id;
    (*idl)->b_nids++;

    memset( (char *) &(*idl)->b_ids[(*idl)->b_nids], '\0',
            ((*idl)->b_nmax - (*idl)->b_nids) * sizeof(ID) );

    return;
}
