cff_string_table_init(cff_string_table_t *pcst, cff_string_item_t *items,
                      int size)
{
    int reprobe = 17;

    memset(items, 0, size * sizeof(*items));
    pcst->items = items;
    pcst->count = 0;
    pcst->size = size;
    while (reprobe != 1 && igcd(size, reprobe) != 1)
        reprobe = (reprobe * 2 + 1) % size;
    pcst->total = 0;
    pcst->reprobe = reprobe;
}
