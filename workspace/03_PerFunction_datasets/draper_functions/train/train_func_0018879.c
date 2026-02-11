list_table_init( list_table_t **tbl )
{
    int i;
    list_table_t* list_tbl = (list_table_t*) malloc(sizeof(list_table_t));

    list_tbl->size = 20;
    list_tbl->nobjs = 0;
    list_tbl->objs = (obj_info_t*) malloc(list_tbl->size * sizeof(obj_info_t));

    for (i = 0; i < list_tbl->size; i++)
    {
        list_tbl->objs[i].tag = -1;
        list_tbl->objs[i].ref = -1;

    }

    *tbl = list_tbl;
}
