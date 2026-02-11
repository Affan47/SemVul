sfnts_reader_seek(sfnts_reader *r, ulong pos)
{
    ulong skipped = 0;

    r->index = -1;
    sfnts_next_elem(r);
    while (skipped + r->length < pos && !r->error) {
        skipped += r->length;
        sfnts_next_elem(r);
    }
    r->offset = pos - skipped;
}
