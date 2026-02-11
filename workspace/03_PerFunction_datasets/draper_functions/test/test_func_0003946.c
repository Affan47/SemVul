vector_split_multi(const char *string, const char *seps,
                   struct vector *vector)
{
    const char *p, *start;
    size_t i, count;


    vector = vector_reuse(vector);


    count = split_multi_count(string, seps);
    if (vector->allocated < count)
        vector_resize(vector, count);


    for (start = string, p = string, i = 0; *p != '\0'; p++)
        if (strchr(seps, *p) != NULL) {
            if (start != p)
                vector->strings[i++] = xstrndup(start, p - start);
            start = p + 1;
        }
    if (start != p)
        vector->strings[i++] = xstrndup(start, p - start);
    vector->count = i;
    return vector;
}
