walinit(Wal *w, job list)
{
    int min;

    min = walscandir(w);
    walread(w, list, min, w->next);


    if (!makenextfile(w)) {
        twarnx("makenextfile");
        exit(1);
    }

    w->cur = w->tail;
}
