pdf_choose_compression_cos(pdf_image_writer *piw, cos_stream_t *s[2], bool force)
{
    long l0, l1;
    int k0, k1;

    l0 = cos_stream_length(s[0]);
    l1 = cos_stream_length(s[1]);

    if ((force && l0 <= l1) || l1 == -1)
        k0 = 1;
    else {
        k0 = s_compr_chooser__get_choice(
            (stream_compr_chooser_state *)piw->binary[2].strm->state, force);
        if (k0 && l0 > 0 && l1 > 0)
            k0--;
        else if (much_bigger__DL(l0, l1))
            k0 = 0;
        else if (much_bigger__DL(l1, l0) || force)
            k0 = 1;
        else
           return;
    }
    k1 = 1 - k0;
    s_close_filters(&piw->binary[k0].strm, piw->binary[k0].target);
    s[k0]->cos_procs->release((cos_object_t *)s[k0], "pdf_image_choose_filter");
    s[k0]->written = 1;
    piw->binary[0].strm = piw->binary[k1].strm;
    s_close_filters(&piw->binary[2].strm, piw->binary[2].target);
    piw->binary[1].strm = piw->binary[2].strm = 0;
    piw->binary[1].target = piw->binary[2].target = 0;
    s[k1]->id = piw->pres->object->id;
    piw->pres->object = (cos_object_t *)s[k1];
    piw->data = s[k1];
    if (piw->alt_writer_count > 3) {
        piw->binary[1] = piw->binary[3];
        piw->binary[3].strm = 0;
        piw->binary[3].target = 0;
    }
    piw->alt_writer_count -= 2;
}
