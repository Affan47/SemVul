explain_buffer_errno_fstatvfs_explanation(explain_string_buffer_t *sb, int
    errnum, const char *syscall_name, int fildes, struct statvfs *data)
{


    (void)data;
    switch (errnum)
    {
    case EBADF:
        explain_buffer_ebadf(sb, fildes, "fildes");
        break;

    case EFAULT:
        explain_buffer_efault(sb, "data");
        break;

    case EINTR:
        explain_buffer_eintr(sb, syscall_name);
        break;

    case EIO:
        explain_buffer_eio(sb);
        break;

    case ENOMEM:
        explain_buffer_enomem_kernel(sb);
        break;

    case ENOSYS:
#if defined(EOPNOTSUPP) && ENOSYS != EOPNOTSUPP
    case EOPNOTSUPP:
#endif
#if defined(ENOTSUP) && (ENOTSUP != EOPNOTSUPP)
    case ENOTSUP:
#endif
        explain_buffer_enosys_fildes(sb, fildes, "fildes", syscall_name);
        break;

    case EOVERFLOW:
        explain_buffer_eoverflow(sb);
        break;

    default:
        explain_buffer_errno_generic(sb, errnum, syscall_name);
        break;
    }
}
