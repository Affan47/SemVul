add_to_list(struct profile_string_list *list, const char *str)
{
    char    *newstr, **newlist;
    unsigned int    newmax;

    if (list->num+1 >= list->max) {
        newmax = list->max + 10;
        newlist = realloc(list->list, newmax * sizeof(char *));
        if (newlist == 0)
            return ENOMEM;
        list->max = newmax;
        list->list = newlist;
    }
    newstr = strdup(str);
    if (newstr == 0)
        return ENOMEM;

    list->list[list->num++] = newstr;
    list->list[list->num] = 0;
    return 0;
}
