save_reductions(void)
{
    register short *isp;
    register short *rp1;
    register short *rp2;
    register int item;
    register int count;
    register reductions *p;
    register short *rend;

    count = 0;
    for (isp = itemset; isp < itemsetend; isp++)
    {
        item = ritem[*isp];
        if (item < 0)
        {
            redset[count++] = -item;
        }
    }

    if (count)
    {
        p = (reductions *) allocate((unsigned) (sizeof(reductions) +
                                        (count - 1) * sizeof(short)));

        p->number = this_state->number;
        p->nreds = count;

        rp1 = redset;
        rp2 = p->rules;
        rend = rp1 + count;

        while (rp1 < rend)
            *rp2++ = *rp1++;

        if (last_reduction)
        {
            last_reduction->next = p;
            last_reduction = p;
        }
        else
        {
            first_reduction = p;
            last_reduction = p;
        }
    }
}
