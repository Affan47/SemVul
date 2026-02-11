gnc_csv_parse_data_free(GncCsvParseData* parse_data)
{


    if (parse_data->raw_mapping != NULL)
    {
        g_mapped_file_unref(parse_data->raw_mapping);
    }

    if (parse_data->file_str.begin != NULL)
        g_free(parse_data->file_str.begin);

    if (parse_data->orig_lines != NULL)
        stf_parse_general_free(parse_data->orig_lines);

    if (parse_data->orig_row_lengths != NULL)
        g_array_free(parse_data->orig_row_lengths, FALSE);

    if (parse_data->options != NULL)
        stf_parse_options_free(parse_data->options);

    if (parse_data->column_types != NULL)
        g_array_free(parse_data->column_types, TRUE);

    if (parse_data->error_lines != NULL)
        g_list_free(parse_data->error_lines);

    if (parse_data->transactions != NULL)
    {
        GList* transactions = parse_data->transactions;


        do
        {
            g_free(transactions->data);
            transactions = g_list_next(transactions);
        }
        while (transactions != NULL);
        g_list_free(parse_data->transactions);
    }

    g_free(parse_data->chunk);
    g_free(parse_data);
}
