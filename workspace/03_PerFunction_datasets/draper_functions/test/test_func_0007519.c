rtbl_format (rtbl_t table, FILE * f)
{
    size_t i, j;

    for (i = 0; i < table->num_columns; i++)
	column_compute_width (table, table->columns[i]);
    if((table->flags & RTBL_HEADER_STYLE_NONE) == 0) {
	for (i = 0; i < table->num_columns; i++) {
	    struct column_data *c = table->columns[i];

	    if(table->column_separator != NULL && i > 0)
		fprintf (f, "%s", table->column_separator);
	    fprintf (f, "%s", get_column_prefix (table, c));
	    if(i == table->num_columns - 1 && c->suffix == NULL)

		fprintf (f, "%-*s", 0, c->header);
	    else
		fprintf (f, "%-*s", (int)c->width, c->header);
	    fprintf (f, "%s", get_column_suffix (table, c));
	}
	fprintf (f, "\n");
    }

    for (j = 0;; j++) {
	int flag = 0;


	for (i = 0; flag == 0 && i < table->num_columns; ++i) {
	    struct column_data *c = table->columns[i];

	    if (c->num_rows > j) {
		++flag;
		break;
	    }
	}
	if (flag == 0)
	    break;

	for (i = 0; i < table->num_columns; i++) {
	    int w;
	    struct column_data *c = table->columns[i];

	    if(table->column_separator != NULL && i > 0)
		fprintf (f, "%s", table->column_separator);

	    w = c->width;

	    if ((c->flags & RTBL_ALIGN_RIGHT) == 0) {
		if(i == table->num_columns - 1 && c->suffix == NULL)

		    w = 0;
		else
		    w = -w;
	    }
	    fprintf (f, "%s", get_column_prefix (table, c));
	    if (c->num_rows <= j)
		fprintf (f, "%*s", w, "");
	    else
		fprintf (f, "%*s", w, c->rows[j].data);
	    fprintf (f, "%s", get_column_suffix (table, c));
	}
	fprintf (f, "\n");
    }
    return 0;
}
