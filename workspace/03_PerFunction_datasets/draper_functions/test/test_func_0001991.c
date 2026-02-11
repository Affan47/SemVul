_archive_write_close(struct archive *_a)
{
    struct archive_write *a = (struct archive_write *)_a;
    int r = ARCHIVE_OK, r1 = ARCHIVE_OK;

    __archive_check_magic(&a->archive, ARCHIVE_WRITE_MAGIC,
        ARCHIVE_STATE_ANY, "archive_write_close");


    if (a->archive.state & ARCHIVE_STATE_DATA)
        r = ((a->format_finish_entry)(a));


    if (a->format_finish != NULL) {
        r1 = (a->format_finish)(a);
        if (r1 < r)
            r = r1;
    }


    if (a->format_destroy != NULL) {
        r1 = (a->format_destroy)(a);
        if (r1 < r)
            r = r1;
    }


    if (a->compressor.finish != NULL) {
        r1 = (a->compressor.finish)(a);
        if (r1 < r)
            r = r1;
    }


    if (a->client_closer != NULL) {
        r1 = (a->client_closer)(&a->archive, a->client_data);
        if (r1 < r)
            r = r1;
    }

    a->archive.state = ARCHIVE_STATE_CLOSED;
    return (r);
}
