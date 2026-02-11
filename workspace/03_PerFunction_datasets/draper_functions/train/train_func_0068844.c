get_next_timing_index(Stasche_lm_dt *sld, const int pgno, const int idx)
{
    int ntasks = sld->ntasks[pgno];

    if (idx == 2 * ntasks - 1) {
        return idx;
    } else {
        return idx + 1;
    }
}
