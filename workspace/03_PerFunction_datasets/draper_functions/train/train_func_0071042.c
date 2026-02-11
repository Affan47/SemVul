ide_sector_write(struct ide_device *s) {
    int64_t sector_num;
    int n, n1;

    s->status  = READY_STAT | SEEK_STAT;
    sector_num = ide_get_sector(s);

    if (IDE_debug)
        fprintf(stderr, "IDE: write sector=%" PRId64 "\n", sector_num);

    n = s->nsector;
    if (n > s->req_nb_sectors)
        n = s->req_nb_sectors;

    if (fseeko(s->file, sector_num * SECTOR_SIZE, SEEK_SET) < 0) {
        fprintf(stderr, "FSEEKO FAILED\n");
        goto fail;
    }
    if (fwrite(s->io_buffer, n * SECTOR_SIZE, 1, s->file) != 1) {
        fprintf(stderr, "FWRITE FAILED\n");
        goto fail;
    }
    fflush(s->file);

    s->nsector -= n;
    if (s->nsector == 0) {
        ide_transfer_stop(s);
    } else {
        n1 = s->nsector;
        if (n1 > s->req_nb_sectors)
            n1 = s->req_nb_sectors;
        ide_transfer_start(s, s->io_buffer, 512 * n1, ide_sector_write);
    }
    ide_set_sector(s, sector_num + n + (s->nsector ? 0 : -1));
    return;

fail:
    ide_abort_command(s);
}
