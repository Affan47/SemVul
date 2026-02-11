ompi_osc_sm_rget(void *origin_addr,
                 int origin_count,
                 struct ompi_datatype_t *origin_dt,
                 int target,
                 OPAL_PTRDIFF_TYPE target_disp,
                 int target_count,
                 struct ompi_datatype_t *target_dt,
                 struct ompi_win_t *win,
                 struct ompi_request_t **ompi_req)
{
    int ret;
    ompi_osc_sm_request_t *request;
    ompi_osc_sm_module_t *module =
        (ompi_osc_sm_module_t*) win->w_osc_module;
    void *remote_address;

    OPAL_OUTPUT_VERBOSE((50, ompi_osc_base_framework.framework_output,
                         "rget: 0x%lx, %d, %s, %d, %d, %d, %s, 0x%lx",
                         (unsigned long) origin_addr, origin_count,
                         origin_dt->name, target, (int) target_disp,
                         target_count, target_dt->name,
                         (unsigned long) win));

    OMPI_OSC_SM_REQUEST_ALLOC(win, request);
    if (NULL == request) return OMPI_ERR_OUT_OF_RESOURCE;
    *ompi_req = &request->super;

    remote_address = ((char*) (module->bases[target])) + module->disp_units[target] * target_disp;

    ret = ompi_datatype_sndrcv(remote_address, target_count, target_dt,
                               origin_addr, origin_count, origin_dt);
    if (OMPI_SUCCESS != ret) {
        OMPI_OSC_SM_REQUEST_RETURN(request);
        return ret;
    }

    OMPI_OSC_SM_REQUEST_COMPLETE(request);

    return OMPI_SUCCESS;
}
