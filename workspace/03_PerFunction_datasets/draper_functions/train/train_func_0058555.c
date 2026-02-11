g726_reset(G726Context* c, int index)
{
    int i;

    c->tbls = G726Tables_pool[index];
    for (i=0; i<2; i++) {
        c->sr[i].mant = 1<<5;
        c->pk[i] = 1;
    }
    for (i=0; i<6; i++) {
        c->dq[i].mant = 1<<5;
    }
    c->yu = 544;
    c->yl = 34816;

    c->y = 544;

    return 0;
}
