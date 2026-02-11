popdir(file_enum * pfen)
{
    dirstack *d = pfen->dstack;

    if (d == 0)
        return false;
    pfen->dirp = d->entry;
    pfen->dstack = d->next;
    gs_free_object(pfen->memory, d, "gp_enumerate_files(popdir)");
    return true;
}
