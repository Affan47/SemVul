fluid_list_str_compare_func (void *a, void *b)
{
    if (a && b) return FLUID_STRCMP ((char *)a, (char *)b);
    if (!a && !b) return 0;
    if (a) return -1;
    return 1;
}
