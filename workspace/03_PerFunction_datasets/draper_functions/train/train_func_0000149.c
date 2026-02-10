walgc(Wal *w)
{
    File *f;

    while (w->head && !w->head->refs) {
        f = w->head;
        w->head = f->next;
        if (w->tail == f) {
            w->tail = f->next;
        }

        w->nfile--;
        unlink(f->path);
        free(f->path);
        free(f);
    }
}
