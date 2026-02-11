rem_get_attr(struct remfs *fs, struct remnode *nod,
                        struct remnode *parent)
{
    int res;
    struct remote *rem = fs->rem;
    struct remdirlist dl;

    dl.flags = REM_LIST_SINGLE;
    dl.num = 0;
    dl.ents = NULL;
    rem_get_hostpath(nod->ent, &dl.hostpath);
    if((rem->flags & REM_DIR_ONLY) != 0)
        rem_dir_only(&dl);

    res = rem->list(rem, &dl);
    if(res == 0) {
        if((dl.flags & REM_LIST_SINGLE) != 0)
            res = rem_list_single(fs, nod, &dl);
        else if((dl.flags & REM_LIST_PARENT) != 0)
            res = rem_list_dir(fs, parent, nod, &dl, nod);
        else
            res = rem_list_dir(fs, nod, NULL, &dl, nod);


        if(parent == NULL && res == -ENOENT) {
            rem_fill_root(fs, nod);
            res = 0;
        }
    }

    rem_free_dirlist(&dl);

    if(res == -ENOENT) {
        nod->attr.valid = av_time() + REM_ST_VALID;
        nod->attr.negative = 1;
    }

    return res;
}
