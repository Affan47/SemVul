ide_sector_read(struct ide_device *s) {
    int64_t sector_num;
    int n;

    s->status  = READY_STAT | SEEK_STAT;
    s->error   = 0;
    sector_num = ide_get_sector(s);
    n          = s->nsector;

    if (!n) {
        ide_transfer_stop(s);
    } else {
        if (IDE_debug)
            fprintf(stderr, "IDE: read sector=%" PRId64 "\n", sector_num);

        if (n > s->req_nb_sectors)
            n = s->req_nb_sectors;

        if (fseeko(s->file, sector_num * SECTOR_SIZE, SEEK_SET) < 0)
            goto fail;
        if (fread(s->io_buffer, n * SECTOR_SIZE, 1, s->file) != 1)
            goto fail;

        if (IDE_debug) fprintf(stderr, "sector read OK\n");

        ide_transfer_start(s, s->io_buffer, 512*n, ide_sector_read);
        s->nsector -= n;
        ide_set_sector(s, sector_num + n + (s->nsector ? 0 : -1));
    }
    return;

fail:
    ide_abort_command(s);
    if (IDE_debug) fprintf(stderr, "sector read FAILED\n");
}
