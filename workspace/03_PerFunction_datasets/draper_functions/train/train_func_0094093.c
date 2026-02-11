pa_sdbm_lock(pa_sdbm_t *db, int type)
{
    pa_status_t status;

    if (!(type == PA_FLOCK_SHARED || type == PA_FLOCK_EXCLUSIVE))
        return PA_EINVAL;

    if (db->flags & SDBM_EXCLUSIVE_LOCK) {
        ++db->lckcnt;
        return PA_SUCCESS;
    }
    else if (db->flags & SDBM_SHARED_LOCK) {


        if (type == PA_FLOCK_EXCLUSIVE)
            return PA_EINVAL;
        ++db->lckcnt;
        return PA_SUCCESS;
    }


    if ((status = pa_file_lock(db->dirf, type)) == PA_SUCCESS)
    {
        pa_finfo_t finfo;
        if ((status = pa_file_info_get(&finfo, PA_FINFO_SIZE, db->dirf))
                != PA_SUCCESS) {
            (void) pa_file_unlock(db->dirf);
            return status;
        }

        SDBM_INVALIDATE_CACHE(db, finfo);

        ++db->lckcnt;
        if (type == PA_FLOCK_SHARED)
            db->flags |= SDBM_SHARED_LOCK;
        else if (type == PA_FLOCK_EXCLUSIVE)
            db->flags |= SDBM_EXCLUSIVE_LOCK;
    }
    return status;
}
