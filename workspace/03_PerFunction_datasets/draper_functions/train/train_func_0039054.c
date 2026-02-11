explain_buffer_errno_snprintf_system_call(explain_string_buffer_t *sb,
    int errnum, char *data, size_t data_size, const char *format, va_list ap)
{
    (void)errnum;
    explain_string_buffer_puts(sb, "snprintf(data = ");
    explain_buffer_pointer(sb, data);
    explain_string_buffer_puts(sb, ", data_size = ");
    explain_buffer_size_t(sb, data_size);
    explain_string_buffer_puts(sb, ", format = ");
    explain_buffer_pathname(sb, format);
    if (format && !explain_is_efault_string(format))
        explain_printf_format_representation(sb, format, ap);
    explain_string_buffer_putc(sb, ')');
}
