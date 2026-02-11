gnc_csv_convert_encoding(GncCsvParseData* parse_data, const char* encoding,
                             GError** error)
{
    gsize bytes_read, bytes_written;


    if (parse_data->file_str.begin != NULL)
        g_free(parse_data->file_str.begin);


    parse_data->file_str.begin = g_convert(parse_data->raw_str.begin,
                                           parse_data->raw_str.end - parse_data->raw_str.begin,
                                           "UTF-8", encoding, &bytes_read, &bytes_written,
                                           error);

    if (parse_data->file_str.begin == NULL)
        return 1;


    parse_data->file_str.end = parse_data->file_str.begin + bytes_written;
    parse_data->encoding = (gchar*)encoding;
    return 0;
}
