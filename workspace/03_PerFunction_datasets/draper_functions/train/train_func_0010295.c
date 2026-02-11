ide_cmd_lba48_transform(struct ide_device *s, int lba48) {
    s->lba48 = lba48;
    if (!s->lba48) {
        if (!s->nsector)
            s->nsector = 256;
    } else {
        if (!s->nsector && !s->hob_nsector)
            s->nsector = 65536;
        else
            s->nsector = (s->hob_nsector << 8) | s->nsector;
    }
}
