_decode_pds(PG_DISPLAY_SET *s, BITBUFFER *bb, PES_BUFFER *p)
{


    if (s->palette) {
        BITBUFFER bb_tmp = *bb;
        uint8_t   id     = bb_read(&bb_tmp, 8);
        unsigned  ii;

        for (ii = 0; ii < s->num_palette; ii++) {
            if (s->palette[ii].id == id) {
                int rr;
                if ( (s->ics && s->ics->composition_descriptor.state == 0) ||
                     (s->pcs && s->pcs->composition_descriptor.state == 0)) {

                    rr = pg_decode_palette_update(bb, &s->palette[ii]);
                } else {
                    rr = pg_decode_palette(bb, &s->palette[ii]);
                }
                if (rr) {
                    s->palette[ii].pts = p->pts;
                    return 1;
                }
                return 0;
            }
        }
    }


    s->palette = realloc(s->palette, sizeof(s->palette[0]) * (s->num_palette + 1));
    memset(&s->palette[s->num_palette], 0, sizeof(s->palette[0]));

    if (pg_decode_palette(bb, &s->palette[s->num_palette])) {
        s->palette[s->num_palette].pts = p->pts;
        s->num_palette++;
        return 1;
    }

    return 0;
}
