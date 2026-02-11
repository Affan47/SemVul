shade_next_init(shade_coord_stream_t * cs,
                const gs_shading_mesh_params_t * params,
                const gs_imager_state * pis)
{
    cs->params = params;
    cs->pctm = &pis->ctm;
    if (data_source_is_stream(params->DataSource)) {


        stream *s = cs->s = params->DataSource.data.strm;

        if ((s->file != 0 && s->file_limit != max_long) ||
            (s->file == 0 && s->strm == 0)
            )
            sseek(s, 0);
    } else {
        s_init(&cs->ds, NULL);
        sread_string(&cs->ds, params->DataSource.data.str.data,
                     params->DataSource.data.str.size);
        cs->s = &cs->ds;
    }
    if (data_source_is_array(params->DataSource)) {
        cs->get_value = cs_next_array_value;
        cs->get_decoded = cs_next_array_decoded;
        cs->align = cs_array_align;
    } else {
        cs->get_value = cs_next_packed_value;
        cs->get_decoded = cs_next_packed_decoded;
        cs->align = cs_packed_align;
    }
    cs->is_eod = cs_eod;
    cs->left = 0;
    cs->ds_EOF = false;
}
