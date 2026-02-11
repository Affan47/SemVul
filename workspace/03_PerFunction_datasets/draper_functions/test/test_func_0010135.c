explain_buffer_errno_realpath_explanation(explain_string_buffer_t *sb,
    int errnum, const char *syscall_name, const char *pathname,
    char *resolved_pathname)
{
    explain_final_t final_component;

    explain_final_init(&final_component);
    final_component.follow_symlink = 1;
    final_component.must_exist = 1;


    switch (errnum)
    {
    case EACCES:
        explain_buffer_eacces(sb, pathname, "pathname", &final_component);
        break;

    case EINVAL:
        if (!pathname)
        {
            explain_buffer_is_the_null_pointer(sb, "pathname");
            return;
        }
        if (!resolved_pathname)
        {
            explain_buffer_is_the_null_pointer(sb, "resolved_pathname");
            return;
        }
        explain_buffer_einval_vague(sb, "pathname");
        break;

    case EIO:
        explain_buffer_eio(sb);
        break;

    case ELOOP:
    case EMLINK:
        explain_buffer_eloop(sb, pathname, "pathname", &final_component);
        break;

    case ENAMETOOLONG:
        explain_buffer_enametoolong
        (
            sb,
            pathname,
            "pathname",
            &final_component
        );
        break;

    case ENOENT:
        explain_buffer_enoent(sb, pathname, "pathname", &final_component);
        break;

    case ENOTDIR:
        explain_buffer_enotdir(sb, pathname, "pathname", &final_component);
        break;

    default:
        explain_buffer_errno_generic(sb, errnum, syscall_name);
        break;
    }
}
