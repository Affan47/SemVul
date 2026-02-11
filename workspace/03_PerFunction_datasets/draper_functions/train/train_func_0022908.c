cpl_image_open(const char * options)
{
    cpl_plot * plot;
    const char * exe = cpl_mplot_imager();
    const char * tmp = CPL_PLOT_TMPFILE;
    FILE * data;


    cpl_ensure(exe != NULL, CPL_ERROR_NULL_INPUT, NULL);

    data = fopen(tmp, "w");

    cpl_error_ensure(data != NULL, CPL_ERROR_FILE_IO, return NULL,
                     "%s", tmp);

    plot = cpl_malloc(sizeof(cpl_plot));

    plot->exe  = exe;
    plot->tmp  = tmp;
    plot->data = data;

    if (cpl_mplot_puts(plot, options)) {
        (void)cpl_mplot_close(plot, "");
        plot = NULL;
        (void)cpl_error_set_where_();
    }

    return plot;
}
