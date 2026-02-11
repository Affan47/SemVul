tuple_get_str (const Tuple * tuple, int nfield, const char * field)
{
    if (nfield < 0)
        nfield = tuple_field_by_name (field);
    if (nfield < 0 || nfield >= TUPLE_FIELDS || tuple_fields[nfield].type != TUPLE_STRING)
        return NULL;

    pthread_mutex_lock (& mutex);

    char * str = NULL;

    TupleVal * val = lookup_val ((Tuple *) tuple, nfield, FALSE, FALSE);
    if (val)
        str = str_ref (val->str);

    pthread_mutex_unlock (& mutex);
    return str;
}
