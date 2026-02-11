opt_blk(b, do_stmts)
     struct block *b;
     int do_stmts;
{
    struct slist *s;
    struct edge *p;
    int i;
    bpf_int32 aval, xval;

#if 0
    for (s = b->stmts; s && s->next; s = s->next)
        if (BPF_CLASS(s->s.code) == BPF_JMP)
        {
            do_stmts = 0;
            break;
        }
#endif


    p = b->in_edges;
    if (p == 0)
    {


        memset((char *) b->val, 0, sizeof(b->val));
    }
    else
    {


        memcpy((char *) b->val, (char *) p->pred->val, sizeof(b->val));


        while ((p = p->next) != NULL)
        {
            for (i = 0; i < N_ATOMS; ++i)
                if (b->val[i] != p->pred->val[i])
                    b->val[i] = 0;
        }
    }
    aval = b->val[A_ATOM];
    xval = b->val[X_ATOM];
    for (s = b->stmts; s; s = s->next)
        opt_stmt(&s->s, b->val, do_stmts);


    if (do_stmts &&
        ((b->out_use == 0 && aval != 0 && b->val[A_ATOM] == aval &&
          xval != 0 && b->val[X_ATOM] == xval) || BPF_CLASS(b->s.code) == BPF_RET))
    {
        if (b->stmts != 0)
        {
            b->stmts = 0;
            done = 0;
        }
    }
    else
    {
        opt_peep(b);
        opt_deadstores(b);
    }


    if (BPF_SRC(b->s.code) == BPF_K)
        b->oval = K(b->s.k);
    else
        b->oval = b->val[X_ATOM];
    b->et.code = b->s.code;
    b->ef.code = -b->s.code;
}
