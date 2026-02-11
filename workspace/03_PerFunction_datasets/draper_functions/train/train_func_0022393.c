_calc_base(struct lms_file_info *finfo)
{
    int i;

    for (i = finfo->path_len - 1; i >= 0; i--)
        if (finfo->path[i] == '/') {
            finfo->base = i;
            return;
        }
}
