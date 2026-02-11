si_del_file_name(SegmentInfo *si, char *buf)
{
    if (si->del_gen < 0) {
        return NULL;
    }
    else {
        return fn_for_generation(buf, si->name, ".del", si->del_gen);
    }
}
