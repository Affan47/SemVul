pdf_put_pattern2(gx_device_pdf *pdev, const gx_drawing_color *pdc,
                 const psdf_set_color_commands_t *ppscc,
                 pdf_resource_t **ppres)
{
    const gs_pattern2_instance_t *pinst =
        (gs_pattern2_instance_t *)pdc->ccolor.pattern;
    const gs_shading_t *psh = pinst->templat.Shading;
    cos_value_t v;
    pdf_resource_t *pres;
    pdf_resource_t *psres;
    cos_dict_t *pcd;
    cos_object_t *psco;
    const gs_range_t *pranges;
    int code = pdf_cs_Pattern_colored(pdev, &v);
    int code1 = 0;
    gs_matrix smat;

    if (code < 0)
        return code;
    code = pdf_alloc_resource(pdev, resourcePattern, gs_no_id, ppres, 0L);
    if (code < 0)
        return code;
    pres = *ppres;
    cos_become(pres->object, cos_type_dict);
    pcd = (cos_dict_t *)pres->object;
    code = pdf_alloc_resource(pdev, resourceShading, gs_no_id, &psres, 0L);
    if (code < 0)
        return code;
    psco = psres->object;
    if (ShadingType(psh) >= 4) {

        cos_become(psco, cos_type_stream);
        code = pdf_put_shading_common(cos_stream_dict((cos_stream_t *)psco),
                                      psh, pinst->shfill, &pranges);
        if (code >= 0)
            code1 = pdf_put_mesh_shading((cos_stream_t *)psco, psh, pranges);
        else

            psres->where_used = 0;
    } else {
        cos_become(psco, cos_type_dict);
        code = pdf_put_shading_common((cos_dict_t *)psco, psh, pinst->shfill, &pranges);
        if (code >= 0)
            code = pdf_put_scalar_shading((cos_dict_t *)psco, psh, pranges);
        else

            psres->where_used = 0;
    }


    gs_currentmatrix(pinst->saved, &smat);
    {
        double xscale = 1.0, yscale = 1.0;
        if (pdev->FormDepth == 0) {
            xscale = 72.0 / pdev->HWResolution[0];
            yscale = 72.0 / pdev->HWResolution[1];
        }

        smat.xx *= xscale, smat.yx *= xscale, smat.tx *= xscale;
        smat.xy *= yscale, smat.yy *= yscale, smat.ty *= yscale;
    }
    if (code < 0 ||
        (code = cos_dict_put_c_key_int(pcd, "/PatternType", 2)) < 0 ||
        (code = cos_dict_put_c_key_object(pcd, "/Shading", psco)) < 0 ||
        (code = cos_dict_put_matrix(pcd, "/Matrix", &smat)) < 0

        )
        return code;
    cos_value_write(&v, pdev);
    pprints1(pdev->strm, " %s\n", ppscc->setcolorspace);
    return code1;
}
