tuple_copy (const Tuple * old)
{
    pthread_mutex_lock (& mutex);

    Tuple * new = tuple_new ();

    for (int f = 0; f < TUPLE_FIELDS; f ++)
    {
        TupleVal * oldval = lookup_val ((Tuple *) old, f, FALSE, FALSE);
        if (oldval)
        {
            TupleVal * newval = lookup_val (new, f, TRUE, FALSE);
            if (tuple_fields[f].type == TUPLE_STRING)
                newval->str = str_ref (oldval->str);
            else
                newval->x = oldval->x;
        }
    }

    new->nsubtunes = old->nsubtunes;

    if (old->subtunes)
        new->subtunes = g_memdup (old->subtunes, sizeof (int) * old->nsubtunes);

    pthread_mutex_unlock (& mutex);
    return new;
}
