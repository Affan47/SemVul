explain_buffer_errno_sethostname_explanation(explain_string_buffer_t *sb,
    int errnum, const char *name, size_t name_size)
{
    size_t          host_name_max;
    ssize_t         name_ssize;


    (void)name;
    name_ssize = name_size;
    switch (errnum)
    {
    case EFAULT:
        explain_buffer_efault(sb, "name");
        break;

    case EINVAL:

        if (name_ssize < 0)
        {
            explain_buffer_einval_too_small(sb, "name_size", name_ssize);
            break;
        }
        host_name_max = explain_get_host_name_max();
        if (host_name_max && name_size > host_name_max)
        {

            goto enametoolong;
        }
        if
        (
            name_size
        &&
            !explain_is_efault_pointer(name, name_size)
        &&
            !name_is_ok(name, name_size)
        )
        {


            explain_buffer_gettext
            (
                sb,


                i18n("the hostname specified contains invalid characters")
            );
            break;
        }

        goto enametoolong;

    case ENAMETOOLONG:
#ifdef EOVERFLOW
    case EOVERFLOW:
#endif
        enametoolong:
        explain_buffer_gettext
        (
            sb,


            i18n("the hostname specified is too long")
        );
        host_name_max = explain_get_host_name_max();
        if (host_name_max && name_size > host_name_max)
        {
            explain_string_buffer_printf
            (
                sb,
                " (%lu > %lu)",
                (unsigned long)name_size,
                (unsigned long)host_name_max
            );
        }
        break;

    case EPERM:
        explain_buffer_gettext
        (
            sb,


            i18n("the process does not have permission to set the hostname")
        );
        explain_buffer_dac_sys_admin(sb);
        break;

    default:
        explain_buffer_errno_generic(sb, errnum, "sethostname");
        break;
    }
}
