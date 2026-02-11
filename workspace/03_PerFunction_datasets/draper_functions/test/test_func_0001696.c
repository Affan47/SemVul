explain_buffer_dvd_physical(explain_string_buffer_t *sb,
    const struct dvd_physical *data)
{
    size_t          j;

    explain_string_buffer_puts(sb, "{ type = ");
    explain_buffer_dvd_struct_type(sb, data->type);
    explain_string_buffer_puts(sb, ", layer_num = ");
    explain_buffer_int(sb, data->layer_num);
    explain_string_buffer_puts(sb, ", layer = {");
    for (j = 0; j < SIZEOF(data->layer); ++j)
        explain_buffer_dvd_layer(sb, &data->layer[j]);
    explain_string_buffer_puts(sb, "}}");
}
