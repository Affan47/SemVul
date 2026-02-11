uniq_add(char *name)
{
    ENTRY item, *i;

    item.key = name;
    item.data = NULL;
    i = hsearch(item, FIND);
    if (i == NULL) {
        vector_add(users, name);
        item.key = users->strings[users->count - 1];
        hsearch(item, ENTER);
    }
}
