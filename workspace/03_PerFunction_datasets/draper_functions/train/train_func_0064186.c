pdf_do_image(gx_device_pdf * pdev, const pdf_resource_t * pres,
             const gs_matrix * pimat, bool in_contents)
{

    double scale = 1;

    if (pimat) {

        const pdf_x_object_t *const pxo = (const pdf_x_object_t *)pres;
        scale = (double)pxo->data_height / pxo->height;
    }
    return pdf_do_image_by_id(pdev, scale, pimat, in_contents, pdf_resource_id(pres));
}
