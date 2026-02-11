explain_buffer_errno_readlink_explanation(explain_string_buffer_t *sb,
    int errnum, const char *pathname, char *data, size_t data_size)
{
    explain_final_t final_component;

    (void)data;
    explain_final_init(&final_component);
    final_component.want_to_read = 1;
    final_component.follow_symlink = 0;

    switch (errnum)
    {
    case EACCES:
        explain_buffer_eacces(sb, pathname, "pathname", &final_component);
        break;

    case EFAULT:
        if (explain_is_efault_path(pathname))
        {
            explain_buffer_efault(sb, "pathname");
            break;
        }
        explain_buffer_efault(sb, "data");
        break;

    case EINVAL:
        if ((ssize_t)data_size <= 0)
        {
            explain_buffer_einval_too_small
            (
                sb,
                "data_size",
                (ssize_t)data_size
            );
        }
        else
        {
            struct stat     st;


            if (lstat(pathname, &st) >= 0)
            {
                explain_string_buffer_puts(sb, "pathname is a ");
                explain_buffer_file_type_st(sb, &st);
                explain_string_buffer_puts(sb, ", not a ");
                explain_buffer_file_type(sb, S_IFLNK);
            }
            else
            {
                explain_string_buffer_puts(sb, "pathname is not a ");
                explain_buffer_file_type(sb, S_IFLNK);
            }
        }
        break;

    case EIO:
        explain_buffer_eio_path(sb, pathname);
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

    case ENOMEM:
        explain_buffer_enomem_kernel(sb);
        break;

    case ENOTDIR:
        explain_buffer_enotdir(sb, pathname, "pathname", &final_component);
        break;

    case ERANGE:
        {
            off_t           actual_size;


            explain_buffer_einval_too_small(sb, "data_size", data_size);


            actual_size = get_actual_size(pathname);
            if (actual_size > 0 && (off_t)data_size < actual_size)
            {
                explain_string_buffer_puts(sb, " (");
                explain_buffer_off_t(sb, actual_size);
                explain_string_buffer_putc(sb, ')');
            }
        }
        break;

    default:
        explain_buffer_errno_generic(sb, errnum, "readlink");
        break;
    }
}
