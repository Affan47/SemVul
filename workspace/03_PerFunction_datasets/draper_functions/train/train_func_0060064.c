do_read(ft_ull & progress1, ft_ull & progress2)
{
    int err = 0;
    if (this_replaying) {
        int items = fscanf(this_persist_file, "%"FT_ULL"\t%"FT_ULL"\n", & progress1, & progress2);
        if (items == 2) {

        } else if (feof(this_persist_file)) {
            this_replaying = false;
        } else {
            ff_log(FC_ERROR, 0, "corrupted persistence file '%s'! expecting two numeric values, found %d",
                    this_persist_path.c_str(), (int) items);
            err = -EFAULT;
        }
    }
    return err;
}
