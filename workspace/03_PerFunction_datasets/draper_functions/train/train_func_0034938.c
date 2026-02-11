initialize_states(void)
{
    register int i;
    register short *start_derives;
    register core *p;

    start_derives = derives[start_symbol];
    for (i = 0; start_derives[i] >= 0; ++i)
        continue;

    p = (core *) MALLOC(sizeof(core) + i*sizeof(short));
    if (p == 0) no_space();

    p->next = 0;
    p->link = 0;
    p->number = 0;
    p->accessing_symbol = 0;
    p->nitems = i;

    for (i = 0;  start_derives[i] >= 0; ++i)
        p->items[i] = rrhs[start_derives[i]];

    first_state = last_state = this_state = p;
    nstates = 1;
}
