explain_buffer_in6_addr(explain_string_buffer_t *sb,
    const struct in6_addr *data)
{
    if (explain_is_efault_pointer(data, sizeof(*data)))
        explain_buffer_pointer(sb, data);
    else
    {
        char            straddr[200];

        inet_ntop(AF_INET6, data, straddr, sizeof(straddr));
        explain_string_buffer_puts(sb, straddr);
    }
}
