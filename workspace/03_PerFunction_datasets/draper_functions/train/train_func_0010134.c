explain_buffer_char_data(explain_string_buffer_t *sb, const void *data,
    size_t data_size)
{
    if (explain_is_efault_pointer(data, data_size))
        explain_buffer_pointer(sb, data);
    else
    {
        explain_string_buffer_putc(sb, '{');
        if (data_size <= A_FEW_BYTES)
            explain_buffer_hexdump(sb, data, data_size);
        else if (explain_option_debug())
            explain_buffer_hexdump(sb, data, data_size);
        else
        {
            explain_buffer_hexdump(sb, data, A_FEW_BYTES);
            explain_string_buffer_puts(sb, ", ...");
        }
        explain_string_buffer_puts(sb, " }");
    }
}
