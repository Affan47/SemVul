check_reg_mem_basics(void)
{
#if HAVE_DECL_RLIMIT_MEMLOCK
    int ret = OMPI_SUCCESS;
    struct rlimit limit;
    char *str_limit = NULL;

    ret = getrlimit(RLIMIT_MEMLOCK, &limit);
    if (0 == ret) {
        if ((long) limit.rlim_cur > (64 * 1024) ||
            limit.rlim_cur == RLIM_INFINITY) {
            return OMPI_SUCCESS;
	} else {
            asprintf(&str_limit, "%ld", (long)limit.rlim_cur);
	}
    } else {
        asprintf(&str_limit, "Unknown");
    }

    opal_show_help("help-mpi-btl-usnic.txt", "check_reg_mem_basics fail",
                   true,
                   ompi_process_info.nodename,
                   str_limit);

    return OMPI_ERR_OUT_OF_RESOURCE;
#else


    return OMPI_SUCCESS;
#endif
}
