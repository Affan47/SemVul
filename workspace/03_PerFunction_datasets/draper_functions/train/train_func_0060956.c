alloc_line_records(ulong cnt)
{
    ulong siz;


    if (cnt <= lines_alo_)
        return;


    siz = cnt * sizeof(lines_[0]);


    if (siz > OSMALMAX)
    {

        cnt = OSMALMAX / sizeof(lines_[0]);
        siz = cnt * sizeof(lines_[0]);


        if (cnt <= lines_alo_)
            return;
    }


    if (lines_ == 0)
        lines_ = (CVmSrcfLine *)t3malloc((size_t)siz);
    else
        lines_ = (CVmSrcfLine *)t3realloc(lines_, (size_t)siz);


    lines_alo_ = cnt;
}
