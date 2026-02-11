explain_buffer_errno_munmap_explanation(explain_string_buffer_t *sb, int errnum,
    const char *syscall_name, void *data, size_t data_size)
{
    int             page_size;


    switch (errnum)
    {
    case EINVAL:
        page_size = explain_getpagesize();
        if (page_size > 0)
        {
            int mask = page_size - 1;
            if ((unsigned long)data & mask)
            {
                explain_buffer_must_be_multiple_of_page_size(sb, "data");
                break;
            }
            if ((unsigned long)data_size & mask)
            {
                explain_buffer_must_be_multiple_of_page_size(sb, "data_size");
                break;
            }
        }
        if (data_size == 0)
        {
            explain_buffer_einval_too_small(sb, "data_size", data_size);
            break;
        }


    default:
        explain_buffer_errno_generic(sb, errnum, syscall_name);
        break;
    }
}
