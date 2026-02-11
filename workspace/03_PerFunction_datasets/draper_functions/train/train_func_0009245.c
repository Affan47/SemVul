GC_clear_hdr_marks(hdr *hhdr)
{
    size_t last_bit = FINAL_MARK_BIT(hhdr -> hb_sz);
    BZERO(hhdr -> hb_marks, sizeof(hhdr->hb_marks));
    set_mark_bit_from_hdr(hhdr, last_bit);
    hhdr -> hb_n_marks = 0;
}
