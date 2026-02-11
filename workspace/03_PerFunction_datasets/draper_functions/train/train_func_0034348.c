compare_type(const type_t *a, const type_t *b)
{
    if (a == b
        || (a->name
            && b->name
            && strcmp(a->name, b->name) == 0))
        return 0;

    return 1;
}
