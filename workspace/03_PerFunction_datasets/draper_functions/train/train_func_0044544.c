explain_buffer_timespec(explain_string_buffer_t *sb,
    const struct timespec *data)
{
    if (explain_is_efault_pointer(data, sizeof(*data)))
        explain_buffer_pointer(sb, data);
    else
        print(sb, data);
}
