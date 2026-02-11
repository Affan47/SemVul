pdfmark_PUT(gx_device_pdf * pdev, gs_param_string * pairs, uint count,
            const gs_matrix * pctm, const gs_param_string * no_objname)
{
    cos_object_t *pco;
    cos_value_t value;
    int code, index;

    if (count != 3)
        return_error(gs_error_rangecheck);
    if ((code = pdf_get_named(pdev, &pairs[0], cos_type_array, &pco)) < 0)
        return code;
    if ((code = pdfmark_scan_int(&pairs[1], &index)) < 0)
        return code;
    if (index < 0)
        return_error(gs_error_rangecheck);
    if (pco->written)
        return_error(gs_error_rangecheck);
    return cos_array_put((cos_array_t *)pco, index,
                cos_string_value(&value, pairs[2].data, pairs[2].size));
}
