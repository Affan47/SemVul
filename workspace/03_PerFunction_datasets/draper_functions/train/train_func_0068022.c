explain_buffer_errno_sprintf_system_call(explain_string_buffer_t *sb, int
    errnum, char *data, const char *format, va_list ap)
{
    (void)errnum;
    explain_string_buffer_puts(sb, "sprintf(data = ");
    explain_buffer_pointer(sb, data);
    explain_string_buffer_puts(sb, ", format = ");
    explain_buffer_pathname(sb, format);
    if (format && !explain_is_efault_string(format))
        explain_printf_format_representation(sb, format, ap);
    explain_string_buffer_putc(sb, ')');

    explain_buffer_dangerous_system_call2(sb->footnotes, "sprintf", "snprintf");
}
