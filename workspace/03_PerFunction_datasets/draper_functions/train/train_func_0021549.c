PyGrammar_RemoveAccelerators(grammar *g)
{
    dfa *d;
    int i;
    g->g_accel = 0;
    d = g->g_dfa;
    for (i = g->g_ndfas; --i >= 0; d++) {
        state *s;
        int j;
        s = d->d_state;
        for (j = 0; j < d->d_nstates; j++, s++) {
            if (s->s_accel)
                PyObject_FREE(s->s_accel);
            s->s_accel = NULL;
        }
    }
}
