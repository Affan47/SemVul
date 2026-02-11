match_table_init( match_table_t **tbl )
{
    uint32 i;
    match_table_t* table = (match_table_t*) malloc(sizeof(match_table_t));

    table->size = 20;
    table->nobjs = 0;
    table->objs = (match_info_t*) malloc(table->size * sizeof(match_info_t));

    for (i = 0; i < table->size; i++) {
        table->objs[i].tag1 = table->objs[i].ref1 = -1;
        table->objs[i].tag2 = table->objs[i].ref2 = -1;
        table->objs[i].flags[0] = table->objs[i].flags[1] = -1;
    }

    *tbl = table;
}
