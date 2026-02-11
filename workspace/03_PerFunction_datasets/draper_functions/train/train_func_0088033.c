reserve(Wal *w, int n)
{
    int r;


    if (!w->use) return 1;

    if (w->cur->free >= n) {
        w->cur->free -= n;
        w->cur->resv += n;
        w->resv += n;
        return n;
    }

    r = needfree(w, n);
    if (r != n) {
        twarnx("needfree");
        return 0;
    }

    w->tail->free -= n;
    w->tail->resv += n;
    w->resv += n;
    if (!balance(w, n)) {

        w->resv -= n;
        w->tail->resv -= n;
        w->tail->free += n;
        return 0;
    }

    return n;
}
