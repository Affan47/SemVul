mangle_gid(int id)
{
    int squash = squash_gid;

    if (exports_anongid() != ANON_NOTSPECIAL)
	squash = exports_anongid();

    return mangle(id, squash);
}
