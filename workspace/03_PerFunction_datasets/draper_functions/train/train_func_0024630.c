gx_concretize_ICC(
    const gs_client_color * pcc,
    const gs_color_space *  pcs,
    frac *                  pconc,
    const gs_imager_state * pis,
    gx_device *dev)
    {

    gsicc_link_t *icc_link;
    gsicc_rendering_param_t rendering_params;
    unsigned short psrc[GS_CLIENT_COLOR_MAX_COMPONENTS], psrc_cm[GS_CLIENT_COLOR_MAX_COMPONENTS];
    int k;
    unsigned short *psrc_temp;
    int num_des_comps;
    int code;
    cmm_dev_profile_t *dev_profile;

    code = dev_proc(dev, get_profile)(dev, &dev_profile);
    num_des_comps = gsicc_get_device_profile_comps(dev_profile);

    rendering_params.black_point_comp = pis->blackptcomp;
    rendering_params.graphics_type_tag = dev->graphics_type_tag;
    rendering_params.override_icc = false;
    rendering_params.preserve_black = gsBKPRESNOTSPECIFIED;
    rendering_params.rendering_intent = pis->renderingintent;
    rendering_params.cmm = gsCMM_DEFAULT;
    for (k = 0; k < pcs->cmm_icc_profile_data->num_comps; k++) {
        psrc[k] = (unsigned short) (pcc->paint.values[k]*65535.0);
    }

    icc_link = gsicc_get_link(pis, dev, pcs, NULL, &rendering_params, pis->memory);
    if (icc_link == NULL) {
        return gs_rethrow(-1, "Could not create ICC link:  Check profiles");
    }

    if (icc_link->is_identity) {
        psrc_temp = &(psrc[0]);
    } else {

        psrc_temp = &(psrc_cm[0]);
        (icc_link->procs.map_color)(dev, icc_link, psrc, psrc_temp, 2);
    }

    for (k = 0; k < num_des_comps; k++){
        pconc[k] = float2frac(((float) psrc_temp[k])/65535.0);
    }

    gsicc_release_link(icc_link);
    return 0;
}
