explain_buffer_format_descr(explain_string_buffer_t *sb,
    const struct format_descr *data)
{
    if (explain_is_efault_pointer(data, sizeof(*data)))
    {
        explain_buffer_pointer(sb, data);
        return;
    }

    explain_string_buffer_puts(sb, "{ device = ");
    explain_buffer_int(sb, data->device);
    explain_string_buffer_puts(sb, ", head = ");
    explain_buffer_int(sb, data->head);
    explain_string_buffer_puts(sb, ", track = ");
    explain_buffer_int(sb, data->track);
    explain_string_buffer_puts(sb, " }");
}
