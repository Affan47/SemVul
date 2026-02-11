pdf_end_write_image(gx_device_pdf * pdev, pdf_image_writer * piw)
{
    pdf_resource_t *pres = piw->pres;

    if (pres) {
        cos_object_t *const pco = pres->object;
        cos_stream_t *const pcs = (cos_stream_t *)pco;
        cos_dict_t *named = piw->named;
        int code;

        if (named) {
            if (pdev->ForOPDFRead) {
                code = cos_dict_put_c_key_bool(named, "/.Global", true);
                if (code < 0)
                    return code;
            }


            code = cos_dict_move_all(cos_stream_dict(pcs), named);
            if (code < 0)
                return code;
            pres->named = true;


            *(cos_object_t *)named = *pco;
            pres->object = COS_OBJECT(named);
        } else if (!pres->named) {
            if (pdev->DetectDuplicateImages) {
                pdf_x_object_t *pxo = (pdf_x_object_t *)piw->pres;
                int height = pxo->height, width = pxo->width;

                code = pdf_substitute_resource(pdev, &piw->pres, resourceXObject, NULL, false);
                if (code < 0)
                    return code;


                pxo = (pdf_x_object_t *)piw->pres;
                pxo->height = height;
                pxo->width = width;
            } else {
                pdf_reserve_object_id(pdev, piw->pres, gs_no_id);
            }


            piw->pres->where_used |= pdev->used_mask;
        }
        code = pdf_add_resource(pdev, pdev->substream_Resources, "/XObject", piw->pres);
        if (code < 0)
            return code;
        return 0;
    } else {
        stream *s = pdev->strm;
        uint KeyLength = pdev->KeyLength;

        stream_puts(s, "BI\n");
        cos_stream_elements_write(piw->data, pdev);
        stream_puts(s, (pdev->binary_ok ? "ID " : "ID\n"));
        pdev->KeyLength = 0;
        cos_stream_contents_write(piw->data, pdev);
        pdev->KeyLength = KeyLength;
        pprints1(s, "\nEI%s\n", piw->end_string);
        COS_FREE(piw->data, "pdf_end_write_image");
        return 1;
    }
}
