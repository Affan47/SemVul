bitcask_nifs_file_pwrite(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    bitcask_file_handle* handle;
    unsigned long offset_ul;
    ErlNifBinary bin;

    if (enif_get_resource(env, argv[0], bitcask_file_RESOURCE, (void**)&handle) &&
        enif_get_ulong(env, argv[1], &offset_ul) &&
        enif_inspect_iolist_as_binary(env, argv[2], &bin))
    {
        unsigned char* buf = bin.data;
        ssize_t bytes_written = 0;
        ssize_t count = bin.size;
        off_t offset = offset_ul;

        while (count > 0)
        {
            bytes_written = pwrite(handle->fd, buf, count, offset);
            if (bytes_written > 0)
            {
                count -= bytes_written;
                offset += bytes_written;
                buf += bytes_written;
            }
            else
            {

                return enif_make_tuple2(env, ATOM_ERROR, errno_atom(env, errno));
            }
        }


        return ATOM_OK;
    }
    else
    {
        return enif_make_badarg(env);
    }
}
