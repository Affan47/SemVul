pdf_cancel_resource(gx_device_pdf * pdev, pdf_resource_t *pres, pdf_resource_type_t rtype)
{

    pres->where_used = 0;
    if (pres->object) {
        pres->object->written = true;
        if (rtype == resourceXObject || rtype == resourceCharProc || rtype == resourceOther
            || rtype > NUM_RESOURCE_TYPES) {
            int code = cos_stream_release_pieces((cos_stream_t *)pres->object);

            if (code < 0)
                return code;
        }
        cos_release(pres->object, "pdf_cancel_resource");
        gs_free_object(pdev->pdf_memory, pres->object, "pdf_cancel_resources");
        pres->object = 0;
    }
    return 0;
}
