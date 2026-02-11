server_resolve_wipe (server_resolve_t *resolve)
{
        if (resolve->path)
                GF_FREE ((void *)resolve->path);

        if (resolve->bname)
                GF_FREE ((void *)resolve->bname);

        loc_wipe (&resolve->resolve_loc);
}
