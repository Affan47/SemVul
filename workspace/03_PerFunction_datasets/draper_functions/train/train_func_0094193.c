cmp_rec(const void *p1, const void *p2)
{
        struct dbg_line *d1 = *(struct dbg_line **)p1;
        struct dbg_line *d2 = *(struct dbg_line **)p2;

        if (d1->hdr->ph_sec < d2->hdr->ph_sec)
                return -1;

        if (d1->hdr->ph_sec == d2->hdr->ph_sec &&
            d1->hdr->ph_usec < d2->hdr->ph_usec)
                return -1;

        if (d1->hdr->ph_sec == d2->hdr->ph_sec &&
            d1->hdr->ph_usec == d2->hdr->ph_usec)
                return 0;

        return 1;
}
