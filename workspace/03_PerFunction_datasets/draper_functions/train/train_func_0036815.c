print_array(const char * const *array)
{
    if (!array)
        return;

    for (; *array != NULL; array++)
        printf("\t\t%s\n", *array);
}
