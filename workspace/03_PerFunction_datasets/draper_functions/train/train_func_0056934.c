ompi_osc_sm_unlock_all(struct ompi_win_t *win)
{
    ompi_osc_sm_module_t *module =
        (ompi_osc_sm_module_t*) win->w_osc_module;
    int ret, i, comm_size;

    comm_size = ompi_comm_size(module->comm);
    for (i = 0 ; i < comm_size ; ++i) {
        ret = ompi_osc_sm_unlock(i, win);
        if (OMPI_SUCCESS != ret) return ret;
    }

    return OMPI_SUCCESS;
}
