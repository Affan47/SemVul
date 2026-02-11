sigar_proc_args_destroy(sigar_t *sigar,
                                           sigar_proc_args_t *procargs)
{
    unsigned int i;

    if (procargs->size) {
        for (i=0; i<procargs->number; i++) {
            free(procargs->data[i]);
        }
        free(procargs->data);
        procargs->number = procargs->size = 0;
    }

    return SIGAR_OK;
}
