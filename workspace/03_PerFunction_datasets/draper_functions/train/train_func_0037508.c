gva_columns_lookup_title (GvaGameStoreColumn column_id)
{
        if (CLAMP (column_id, 0, G_N_ELEMENTS (column_info)) != column_id)
                return NULL;

        return column_info[column_id].title;
}
