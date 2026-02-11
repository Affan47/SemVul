stde_seek_ti(SegmentTermDocEnum *stde, TermInfo *ti)
{
    if (NULL == ti) {
        stde->doc_freq = 0;
    }
    else {
        stde->count = 0;
        stde->doc_freq = ti->doc_freq;
        stde->doc_num = 0;
        stde->skip_doc = 0;
        stde->skip_count = 0;
        stde->num_skips = stde->doc_freq / stde->skip_interval;
        stde->frq_ptr = ti->frq_ptr;
        stde->prx_ptr = ti->prx_ptr;
        stde->skip_ptr = ti->frq_ptr + ti->skip_offset;
        is_seek(stde->frq_in, ti->frq_ptr);
        stde->have_skipped = false;
    }
}
