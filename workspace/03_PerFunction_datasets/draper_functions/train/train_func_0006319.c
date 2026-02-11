disclose(int how, bool taken)
{
    char	c = 0, defquery;
    char	qbuf[QBUFSZ];
    bool ask;

    if (invent)
    {
        if(taken)
        {
            sprintf(qbuf,"Do you want to see what you had when you %s?",
                    (how == QUIT) ? "quit" : "died");
        }
        else
        {
            strcpy(qbuf,"Do you want your possessions identified?");
        }
        ask = should_query_disclose_option('i', &defquery);
        if (!done_stopprint)
        {
            c = ask ? yn_function(qbuf, ynqchars, defquery) : defquery;
            if (c == 'y')
            {
                struct obj *obj;

                for (obj = invent; obj; obj = obj->nobj)
                {
                    makeknown(obj->otyp);
                    obj->known = obj->bknown = obj->dknown = obj->rknown = 1;
                }
                display_inventory((char *)0, true);
                container_contents(invent, true, true);
            }
            if (c == 'q')
            {
                done_stopprint++;
            }
        }
    }

    ask = should_query_disclose_option('a', &defquery);
    if (!done_stopprint)
    {
        c = ask ? yn_function("Do you want to see your attributes?",
                              ynqchars, defquery) : defquery;
        if (c == 'y')
        {
            enlightenment(how >= PANICKED ? 1 : 2);
        }
        if (c == 'q')
        {
            done_stopprint++;
        }
    }
    ask = should_query_disclose_option('v', &defquery);
    if (!done_stopprint)
    {
        list_vanquished(defquery, ask);
    }
    ask = should_query_disclose_option('g', &defquery);
    if (!done_stopprint)
    {
        list_genocided(defquery, ask);
    }
    ask = should_query_disclose_option('c', &defquery);
    if (!done_stopprint)
    {
        c = ask ? yn_function("Do you want to see your conduct?",
                              ynqchars, defquery) : defquery;
        if (c == 'y')
        {
            show_conduct(how >= PANICKED ? 1 : 2);
        }
        if (c == 'q')
        {
            done_stopprint++;
        }
    }
}
