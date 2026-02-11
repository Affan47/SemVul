explain_buffer_dvd_manufact(explain_string_buffer_t *sb,
    const struct dvd_manufact *data)
{
    explain_string_buffer_puts(sb, "{ type = ");
    explain_buffer_dvd_struct_type(sb, data->type);
    explain_string_buffer_puts(sb, ", layer_num = ");
    explain_buffer_int(sb, data->layer_num);
    explain_string_buffer_puts(sb, ", len = ");
    explain_buffer_int(sb, data->len);
    explain_string_buffer_puts(sb, ", value = {");
    if (data->len > 0)
    {
        size_t          len;

        len = data->len;
        if (len > sizeof(data->value))
            len = sizeof(data->value);
        if (len > 8)
        {
            explain_buffer_hexdump(sb, data->value, 8);
            explain_string_buffer_puts(sb, " ...");
        }
        else
            explain_buffer_hexdump(sb, data->value, len);
        explain_string_buffer_puts(sb, "}");
    }
    explain_string_buffer_puts(sb, " }");
}
