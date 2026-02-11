cos_value_write_spaced(const cos_value_t *pcv, gx_device_pdf *pdev,
                       bool do_space, gs_id object_id)
{
    stream *s = pdev->strm;

    switch (pcv->value_type) {
    case COS_VALUE_SCALAR:
    case COS_VALUE_CONST:
        if (do_space)
            switch (pcv->contents.chars.data[0]) {
            case '/': case '(': case '<': break;
            default: stream_putc(s, ' ');
            }
        return pdf_write_value(pdev, pcv->contents.chars.data,
                        pcv->contents.chars.size, object_id);
    case COS_VALUE_RESOURCE:
        pprintld1(s, "/R%ld", pcv->contents.object->id);
        break;
    case COS_VALUE_OBJECT: {
        cos_object_t *pco = pcv->contents.object;

        if (!pco->id) {
            if (do_space &&
                !(pco->cos_procs == cos_type_array ||
                  pco->cos_procs == cos_type_dict)
                ) {

                stream_putc(s, ' ');
            }
            return cos_write(pco, pdev, object_id);
        }
        if (do_space)
            stream_putc(s, ' ');
        pprintld1(s, "%ld 0 R", pco->id);
        if (pco->cos_procs == cos_type_reference)
            pco->id = 0;
        break;
    }
    default:
        return_error(gs_error_Fatal);
    }
    return 0;
}
