rtbl_get_column_by_id (rtbl_t table, unsigned int id)
{
    size_t i;
    for(i = 0; i < table->num_columns; i++)
	if(table->columns[i]->column_id == id)
	    return table->columns[i];
    return NULL;
}
