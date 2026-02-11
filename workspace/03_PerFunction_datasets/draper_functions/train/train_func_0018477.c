explain_buffer_eperm_chown(explain_string_buffer_t *sb,
    const char *pathname, int owner, int group, const char *pathname_caption,
    explain_final_t *final_component)
{
    int             chown_restricted;


    chown_restricted = !!pathconf(pathname, _PC_CHOWN_RESTRICTED);
    if (owner >= 0 && chown_restricted && group < 0)
        final_component->want_to_modify_inode = 0;


    if
    (
        explain_buffer_errno_path_resolution
        (
            sb,
            EPERM,
            pathname,
            pathname_caption,
            final_component
        )
    >=
        0
    )
        return;


    {
        struct stat     st;

        if (stat(pathname, &st) >= 0)
        {
            if
            (
                explain_buffer_eperm_chown_st
                (
                    sb,
                    pathname,
                    &st,
                    chown_restricted,
                    owner,
                    group,
                    pathname_caption,
                    final_component
                )
            >=
                0
            )
                return;
        }
    }

    explain_buffer_eperm_chown_vague(sb, owner, group);
}
