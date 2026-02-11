globus_guc_transfer_update(
    const char *                        src_url,
    const char *                        dst_url,
    const char *                        src_fname,
    const char *                        dst_fname)
{

    if(src_url != NULL && dst_url != NULL)
    {
        globus_libc_fprintf(stdout, _GASCSL("Source: %s\nDest:   %s\n"),
            src_url,
            dst_url);
    }

    if(src_fname != NULL && dst_fname != NULL)
    {
        if(!strcmp(src_fname, dst_fname))
        {
            globus_libc_fprintf(stdout, "  %s\n", src_fname);
        }
        else
        {
            globus_libc_fprintf(stdout, "  %s  ->  %s\n",
                src_fname, dst_fname);
        }
    }
}
