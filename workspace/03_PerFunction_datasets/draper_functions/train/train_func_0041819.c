GC_push_next_marked(h)
struct hblk *h;
{
    register hdr * hhdr;

    h = GC_next_used_block(h);
    if (h == 0) return(0);
    hhdr = HDR(h);
    GC_push_marked(h, hhdr);
    return(h + OBJ_SZ_TO_BLOCKS(hhdr -> hb_sz));
}
