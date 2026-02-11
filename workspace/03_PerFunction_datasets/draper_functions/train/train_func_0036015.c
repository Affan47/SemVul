GC_remove_header(struct hblk *h)
{
    hdr **ha;
    GET_HDR_ADDR(h, ha);
    free_hdr(*ha);
    *ha = 0;
}
