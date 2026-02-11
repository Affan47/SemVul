explain_buffer_dac_override(explain_string_buffer_t *sb)
{
    if (explain_capability_dac_override())
        return;
    explain_string_buffer_puts(sb, ", ");
    explain_buffer_and_the_process_is_not_privileged(sb);
#ifdef HAVE_SYS_CAPABILITY_H
    if (explain_option_dialect_specific())
    {
        explain_buffer_does_not_have_capability(sb, "DAC_OVERRIDE");
    }
#endif
}
