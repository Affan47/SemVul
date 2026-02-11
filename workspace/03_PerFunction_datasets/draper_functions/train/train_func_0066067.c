explain_buffer_errno_rmdir_explanation(explain_string_buffer_t *sb,
    int errnum, const char *syscall_name, const char *pathname)
{
    explain_final_t final_component;

    explain_final_init(&final_component);
    final_component.want_to_unlink = 1;
    final_component.must_be_a_st_mode = 1;
    final_component.st_mode = S_IFDIR;

    switch (errnum)
    {
    case EACCES:
        explain_buffer_eacces(sb, pathname, "pathname", &final_component);
        break;

    case EBUSY:
        if (last_component_is_dot(pathname))
        {

            goto case_einval;
        }
        explain_buffer_gettext
        (
            sb,


            i18n("pathname is currently in use by the system or some process "
            "that prevents its removal")
        );
        explain_buffer_path_to_pid(sb, pathname);
#ifdef __linux__
        if (explain_option_dialect_specific())
        {
            explain_string_buffer_puts(sb->footnotes, "; ");
            explain_buffer_gettext
            (
                sb->footnotes,


                i18n("note that pathname is currently used as a mount point "
                "or is the root directory of the calling process")
            );
        }
#endif
        break;

    case EFAULT:
        explain_buffer_efault(sb, "pathname");
        break;

    case EINVAL:
        case_einval:
        explain_buffer_gettext
        (
            sb,


            i18n("pathname has \".\" as last component")
        );
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

    case EEXIST:
    case ENOTEMPTY:
        if (last_component_is_dotdot(pathname))
        {
            explain_buffer_gettext
            (
                sb,


                i18n("pathname has \"..\" as its final component")
            );
        }
        else
        {
            int             count;

            explain_buffer_gettext
            (
                sb,


                i18n("pathname is not an empty directory; that is, it "
                "contains entries other than \".\" and \"..\"")
            );
            count = explain_count_directory_entries(pathname);
            if (count > 0)
                explain_string_buffer_printf(sb, " (%d)", count);
        }
        break;

    case EPERM:
        if
        (
            explain_buffer_errno_path_resolution
            (
                sb,
                errnum,
                pathname,
                "pathname",
                &final_component
            )
        )
        {
            explain_buffer_eperm_unlink(sb, pathname, "pathname", syscall_name);
        }
        break;

    case EROFS:
        explain_buffer_erofs(sb, pathname, "pathname");
        break;

    default:
        explain_buffer_errno_generic(sb, errnum, syscall_name);
        break;
    }

    explain_buffer_note_if_still_exists(sb, pathname, "pathname");
}
