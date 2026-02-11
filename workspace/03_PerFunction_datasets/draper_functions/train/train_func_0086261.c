gx_concretize_CIEA(const gs_client_color * pc, const gs_color_space * pcs_in,
                   frac * pconc, const gs_imager_state * pis, gx_device *dev)
{
    int code;
    gs_color_space *pcs_icc;
    gs_client_color scale_pc;
    gs_color_space *pcs = (gs_color_space *) pcs_in;

    if_debug1m('c', dev->memory, "[c]concretize CIEA %g\n", pc->paint.values[0]);


    if (pcs->icc_equivalent == NULL) {
        code = gx_ciea_to_icc(&pcs_icc, pcs, pis->memory->stable_memory);
    } else {

        pcs_icc = pcs->icc_equivalent;
    }


    if (check_range(&(pcs->params.a->RangeA), 1)) {
        return((pcs_icc->type->concretize_color)(pc, pcs_icc, pconc, pis, dev));
    }

    rescale_input_color(&(pcs->params.a->RangeA), 1, pc, &scale_pc);

    return((pcs_icc->type->concretize_color)(&scale_pc, pcs_icc, pconc, pis, dev));
}
