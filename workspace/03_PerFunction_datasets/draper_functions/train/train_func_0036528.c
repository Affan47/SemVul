pdf_make_form_dict(gx_device_pdf * pdev, const gs_pdf14trans_params_t * pparams,
                            const gs_imager_state * pis,
                            const cos_dict_t *group_dict, cos_dict_t *form_dict)
{
    cos_array_t *bbox_array;
    float bbox[4];
    gs_rect bbox_rect;
    int code;

    code = gs_bbox_transform(&pparams->bbox, &ctm_only(pis), &bbox_rect);
    if (code < 0)
        return code;
    bbox[0] = bbox_rect.p.x;
    bbox[1] = bbox_rect.p.y;
    bbox[2] = bbox_rect.q.x;
    bbox[3] = bbox_rect.q.y;
    code = cos_dict_put_c_key_string(form_dict, "/Type", (const byte *)"/XObject", 8);
    if (code < 0)
        return code;
    code = cos_dict_put_c_key_string(form_dict, "/Subtype", (const byte *)"/Form", 5);
    if (code < 0)
        return code;
    code = cos_dict_put_c_key_int(form_dict, "/FormType", 1);
    if (code < 0)
        return code;
    code = cos_dict_put_c_key_string(form_dict, "/Matrix", (const byte *)"[1 0 0 1 0 0]", 13);
    if (code < 0)
        return code;
    bbox_array = cos_array_from_floats(pdev, bbox, 4, "pdf_begin_transparency_group");
    if (bbox_array == NULL)
        return_error(gs_error_VMerror);
    code = cos_dict_put_c_key_object(form_dict, "/BBox", (cos_object_t *)bbox_array);
    if (code < 0)
        return code;
    return cos_dict_put_c_key_object(form_dict, "/Group", (cos_object_t *)group_dict);
}
