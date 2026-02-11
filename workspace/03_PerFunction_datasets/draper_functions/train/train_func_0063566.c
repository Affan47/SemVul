del234(tree234 * t, void *e)
{
    int index;
    if (!findrelpos234(t, e, NULL, REL234_EQ, &index))
	return NULL;
    return delpos234_internal(t, index);
}
