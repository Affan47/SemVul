meh_hash(meh_hash_id hash_id, const unsigned char* data,
                     size_t len, unsigned char* output)
{
    meh_error_t error;
    MehHash t;

    t = meh_get_hash(hash_id);

    if (NULL == t)
        return MEH_ERROR;

    if ((error = meh_update_hash(t, data, len)) != MEH_OK)
    {
        meh_destroy_hash(t);
        return error;
    }

    if ((error = meh_finish_hash(t, output)) != MEH_OK)
    {
        meh_destroy_hash(t);
        return error;
    }

    meh_destroy_hash(t);

    return MEH_OK;
}
