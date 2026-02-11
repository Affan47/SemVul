ompi_osc_sm_attach(struct ompi_win_t *win, void *base, size_t len)
{
    ompi_osc_sm_module_t *module =
        (ompi_osc_sm_module_t*) win->w_osc_module;

    if (module->flavor != MPI_WIN_FLAVOR_DYNAMIC) {
        return MPI_ERR_RMA_ATTACH;
    }
    return OMPI_SUCCESS;
}
