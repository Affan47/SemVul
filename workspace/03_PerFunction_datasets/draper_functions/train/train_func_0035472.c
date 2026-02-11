lookup(int num, LOOKUP_ITEM *items)
{
    int i = 0;
    while (0 <= items[i].num) {
        if (items[i].num == num)
            return items[i].str;
        i++;
    }
    return "(unknown)";
}
