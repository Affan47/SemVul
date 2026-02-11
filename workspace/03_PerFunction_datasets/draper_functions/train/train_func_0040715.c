GC_remove_counts(struct hblk *h, size_t sz)
{
    register struct hblk * hbp;
    for (hbp = h+1; (char *)hbp < (char *)h + sz; hbp += 1) {
        SET_HDR(hbp, 0);
    }
}
