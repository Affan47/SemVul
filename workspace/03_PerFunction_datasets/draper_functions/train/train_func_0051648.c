filermjob(File *f, job j)
{
    if (!f) return;
    if (f != j->file) return;
    j->fnext->fprev = j->fprev;
    j->fprev->fnext = j->fnext;
    j->fnext = 0;
    j->fprev = 0;
    j->file = NULL;
    f->w->alive -= j->walused;
    j->walused = 0;
    filedecref(f);
}
