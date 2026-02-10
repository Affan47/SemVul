add_roots(void * start, void * end)
{
    void *tmp;
    if (start > end) {
        tmp = start;
        start = end;
        end = tmp;
    }
    root_ranges[root_ranges_used].start = start;
    root_ranges[root_ranges_used].end = end;
    root_ranges_used++;

    if (root_ranges_used >= ROOT_RANGES_LIMIT) {
        fputs("Root OverFlow", stderr);
        abort();
    }
}
