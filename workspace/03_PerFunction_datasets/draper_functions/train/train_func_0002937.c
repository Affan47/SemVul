qhasharr_put_by_obj(qhasharr_t *tbl, const void *name, size_t namesize,
                         const void *data, size_t datasize) {
    if (tbl == NULL || name == NULL || namesize == 0 || data == NULL
            || datasize == 0) {
        errno = EINVAL;
        return false;
    }

    qhasharr_data_t *tbldata = tbl->data;
    qhasharr_slot_t *tblslots = get_slots(tbl);


    if (tbldata->usedslots >= tbldata->maxslots) {
        errno = ENOBUFS;
        return false;
    }


    uint32_t hash = qhashmurmur3_32(name, namesize) % tbldata->maxslots;


    if (tblslots[hash].count == 0) {

        if (put_data(tbl, hash, hash, name, namesize, data, datasize,
                     1) == false) {
            return false;
        }
    } else if (tblslots[hash].count > 0) {

        int idx = get_idx(tbl, name, namesize, hash);
        if (idx >= 0) {

            qhasharr_remove_by_idx(tbl, idx);
            return qhasharr_put_by_obj(tbl, name, namesize, data, datasize);
        } else {

            int idx = find_avail(tbl, hash);
            if (idx < 0) {
                errno = ENOBUFS;
                return false;
            }


            if (put_data(tbl, idx, hash, name, namesize, data, datasize,
                         COLLISION_MARK) == false) {
                return false;
            }


            tblslots[hash].count++;
        }
    } else {


        int idx = find_avail(tbl, hash + 1);
        if (idx < 0) {
            errno = ENOBUFS;
            return false;
        }


        copy_slot(tbl, idx, hash);
        remove_slot(tbl, hash);


        if (tblslots[idx].link != -1) {
            tblslots[tblslots[idx].link].hash = idx;
        }
        if (tblslots[idx].count == EXTBLOCK_MARK) {
            tblslots[tblslots[idx].hash].link = idx;
        }


        if (put_data(tbl, hash, hash, name, namesize, data, datasize,
                     1) == false) {
            return false;
        }
    }

    return true;
}
