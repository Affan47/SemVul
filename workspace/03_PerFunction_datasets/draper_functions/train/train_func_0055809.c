explain_buffer_ebadf_not_open_for_writing(explain_string_buffer_t *sb,
    const char *caption, int flags)
{
    explain_string_buffer_printf_gettext
    (
        sb,


        i18n("the %s argument does not refer to an object that is open for "
            "writing"),
        caption
    );
    if (flags >= 0)
    {
        explain_string_buffer_puts(sb, " (");
        explain_buffer_open_flags(sb, flags);
        explain_string_buffer_putc(sb, ')');
    }
}
