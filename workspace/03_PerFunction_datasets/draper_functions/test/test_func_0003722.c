load_sini(VMG_ ulong siz)
{
    char hdr[12];
    ulong siz_rem;
    ulong hdr_siz;
    ulong init_cnt;
    ulong init_rem;


    fp_->copy_data(hdr, 12);
    hdr_siz = t3rp4u(hdr);
    static_cs_ofs_ = t3rp4u(hdr + 4);
    init_cnt = t3rp4u(hdr + 8);


    if (hdr_siz > 12)
        fp_->skip_ahead(hdr_siz - 12);


    siz_rem = siz - hdr_siz;


    for (init_rem = init_cnt ; init_rem != 0 ; )
    {
        size_t cur;
        CVmStaticInitPage *pg;


        cur = VM_STATIC_INIT_PAGE_MAX;
        if (init_rem < cur)
            cur = (size_t)init_rem;


        pg = new CVmStaticInitPage(cur);


        if (static_tail_ != 0)
            static_tail_->nxt_ = pg;
        else
            static_head_ = pg;
        static_tail_ = pg;


        pg->data_ = fp_->alloc_and_read(cur * 6, 0, siz_rem);


        init_rem -= cur;
        siz_rem -= cur * 6;
    }


    if (siz_rem != 0)
        fp_->skip_ahead(siz_rem);
}
