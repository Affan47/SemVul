rtbl_get_column (rtbl_t table, const char *column)
{
    size_t i;
    for(i = 0; i < table->num_columns; i++)
	if(strcmp(table->columns[i]->header, column) == 0)
	    return table->columns[i];
    return NULL;
}
