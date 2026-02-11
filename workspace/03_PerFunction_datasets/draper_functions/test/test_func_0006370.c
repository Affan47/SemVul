regmulti_save_enough_space_for_new_file(cregmulti *m, u32 filesize)
{
    if (!m)
    {   errprintf("invalid param\n");
        return false;
    }

    if (m->count >= m->maxitems)
        return false;
    if (m->usedsize + filesize > m->maxblksize)
        return false;
    return true;
}
