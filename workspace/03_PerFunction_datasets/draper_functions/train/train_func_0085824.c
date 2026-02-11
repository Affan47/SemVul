explain_buffer_errno_unlink_explanation(explain_string_buffer_t *sb,
    int errnum, const char *syscall_name, const char *pathname)
{
    explain_final_t final_component;

    explain_final_init(&final_component);
    final_component.want_to_unlink = 1;

    switch (errnum)
    {
    case EACCES:
        explain_buffer_eacces(sb, pathname, "pathname", &final_component);
        break;

    case EBUSY:
        explain_string_buffer_puts
        (
            sb,


            i18n("the pathname is being used by the system or another "
            "process and the implementation considers this an error")
        );
        explain_buffer_path_to_pid(sb, pathname);
        break;

    case EFAULT:
        explain_buffer_efault(sb, "pathname");
        break;

    case EIO:
        explain_buffer_eio_path(sb, pathname);
        break;

    case EISDIR:
        explain_string_buffer_puts
        (
            sb,


            i18n("the named file is a directory; directories may not be "
            "unlinked, use rmdir(2) or remove(3) instead")
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

    case EPERM:
#ifndef __linux__


        if (explain_pathname_is_a_directory(pathname))
        {
            explain_string_buffer_puts
            (
                sb,


                i18n("the system does not allow unlinking of directories, or "
                "unlinking of directories requires privileges that the process "
                "does not have")
            );
            break;
        }
#endif
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
            break;
        }
        goto generic;

    case EROFS:
        explain_buffer_erofs(sb, pathname, "pathname");
        break;

    default:
        generic:
        explain_buffer_errno_generic(sb, errnum, syscall_name);
        break;
    }

    explain_buffer_note_if_still_exists(sb, pathname, "pathname");
}
