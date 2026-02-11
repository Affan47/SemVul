archive_read_next_header2(struct archive *_a, struct archive_entry *entry)
{
    struct archive_read *a = (struct archive_read *)_a;
    int slot, ret;

    __archive_check_magic(_a, ARCHIVE_READ_MAGIC,
        ARCHIVE_STATE_HEADER | ARCHIVE_STATE_DATA,
        "archive_read_next_header");

    ++_a->file_count;
    archive_entry_clear(entry);
    archive_clear_error(&a->archive);


    if (a->format == NULL) {
        slot = choose_format(a);
        if (slot < 0) {
            a->archive.state = ARCHIVE_STATE_FATAL;
            return (ARCHIVE_FATAL);
        }
        a->format = &(a->formats[slot]);
    }


    if (a->archive.state == ARCHIVE_STATE_DATA) {
        ret = archive_read_data_skip(&a->archive);
        if (ret == ARCHIVE_EOF) {
            archive_set_error(&a->archive, EIO, "Premature end-of-file.");
            a->archive.state = ARCHIVE_STATE_FATAL;
            return (ARCHIVE_FATAL);
        }
        if (ret != ARCHIVE_OK)
            return (ret);
    }


    a->header_position = a->archive.file_position;

    ret = (a->format->read_header)(a, entry);


    switch (ret) {
    case ARCHIVE_EOF:
        a->archive.state = ARCHIVE_STATE_EOF;
        break;
    case ARCHIVE_OK:
        a->archive.state = ARCHIVE_STATE_DATA;
        break;
    case ARCHIVE_WARN:
        a->archive.state = ARCHIVE_STATE_DATA;
        break;
    case ARCHIVE_RETRY:
        break;
    case ARCHIVE_FATAL:
        a->archive.state = ARCHIVE_STATE_FATAL;
        break;
    }

    a->read_data_output_offset = 0;
    a->read_data_remaining = 0;
    return (ret);
}
