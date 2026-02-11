explain_buffer_eafnosupport(explain_string_buffer_t *sb, int fildes,
    const char *fildes_caption, const struct sockaddr *sock_addr,
    const char *sock_addr_caption)
{
    int             fildes_af;

    (void)sock_addr;
    fildes_af = explain_fildes_to_address_family(fildes);
    if (fildes_af >= 0)
    {
        char            aftxt[30];
        explain_string_buffer_t aftxt_sb;

        explain_string_buffer_init(&aftxt_sb, aftxt, sizeof(aftxt));
        explain_buffer_address_family(&aftxt_sb, fildes_af);
        explain_string_buffer_printf_gettext
        (
            sb,


            i18n("%s does not have the correct address family, "
                "%s address family is %s"),
            sock_addr_caption,
            fildes_caption,
            aftxt
        );
    }
    else
    {
        explain_string_buffer_printf_gettext
        (
            sb,


            i18n("%s does not have the same address family as %s"),
            sock_addr_caption,
            fildes_caption
        );
    }
}
