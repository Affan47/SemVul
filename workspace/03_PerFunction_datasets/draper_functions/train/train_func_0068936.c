gnc_csv_parse(GncCsvParseData* parse_data, gboolean guessColTypes, GError** error)
{

    int i, max_cols = 0;

    if (parse_data->orig_lines != NULL)
    {
        stf_parse_general_free(parse_data->orig_lines);
    }


    if (parse_data->file_str.begin != NULL)
    {

        parse_data->orig_lines = stf_parse_general(parse_data->options, parse_data->chunk,
                                 parse_data->file_str.begin,
                                 parse_data->file_str.end);
    }

    else
    {
        parse_data->orig_lines = g_ptr_array_new();
    }


    if (parse_data->orig_row_lengths != NULL)
        g_array_free(parse_data->orig_row_lengths, FALSE);

    parse_data->orig_row_lengths =
        g_array_sized_new(FALSE, FALSE, sizeof(int), parse_data->orig_lines->len);

    g_array_set_size(parse_data->orig_row_lengths, parse_data->orig_lines->len);
    parse_data->orig_max_row = 0;
    for (i = 0; i < parse_data->orig_lines->len; i++)
    {
        int length = ((GPtrArray*)parse_data->orig_lines->pdata[i])->len;
        parse_data->orig_row_lengths->data[i] = length;
        if (length > parse_data->orig_max_row)
            parse_data->orig_max_row = length;
    }


    if (parse_data->orig_lines == NULL)
    {
        g_set_error(error, 0, 0, "Parsing failed.");
        return 1;
    }


    for (i = 0; i < parse_data->orig_lines->len; i++)
    {
        if (max_cols < ((GPtrArray*)(parse_data->orig_lines->pdata[i]))->len)
            max_cols = ((GPtrArray*)(parse_data->orig_lines->pdata[i]))->len;
    }

    if (guessColTypes)
    {

        if (parse_data->column_types != NULL)
            g_array_free(parse_data->column_types, TRUE);


        parse_data->column_types = g_array_sized_new(FALSE, FALSE, sizeof(int),
                                   max_cols);
        g_array_set_size(parse_data->column_types, max_cols);

        for (i = 0; i < parse_data->column_types->len; i++)
        {
            parse_data->column_types->data[i] = GNC_CSV_NONE;
        }
    }
    else
    {


        int i = parse_data->column_types->len;
        g_array_set_size(parse_data->column_types, max_cols);
        for (; i < parse_data->column_types->len; i++)
        {
            parse_data->column_types->data[i] = GNC_CSV_NONE;
        }
    }

    return 0;
}
