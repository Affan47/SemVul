_archive_write_finish(struct archive *_a)
{
    struct archive_write *a = (struct archive_write *)_a;
    int r = ARCHIVE_OK;

    __archive_check_magic(&a->archive, ARCHIVE_WRITE_MAGIC,
        ARCHIVE_STATE_ANY, "archive_write_finish");
    if (a->archive.state != ARCHIVE_STATE_CLOSED)
        r = archive_write_close(&a->archive);


    free((void *)(uintptr_t)(const void *)a->nulls);
    archive_string_free(&a->archive.error_string);
    a->archive.magic = 0;
    free(a);
    return (r);
}
