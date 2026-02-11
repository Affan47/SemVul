dv_format_frame(DVVideoContext* c, uint8_t* buf)
{
    int chan, i, j, k;

    for (chan = 0; chan < c->sys->n_difchan; chan++) {
        for (i = 0; i < c->sys->difseg_size; i++) {
            memset(buf, 0xff, 80 * 6);


            buf += dv_write_dif_id(dv_sect_header, chan, i, 0, buf);
            buf += dv_write_pack((c->sys->dsf ? dv_header625 : dv_header525), c, buf);
            buf += 72;


            for (j = 0; j < 2; j++) {
                buf += dv_write_dif_id(dv_sect_subcode, chan, i, j, buf);
                for (k = 0; k < 6; k++)
                     buf += dv_write_ssyb_id(k, (i < c->sys->difseg_size/2), buf) + 5;
                buf += 29;
            }


            for (j = 0; j < 3; j++) {
                buf += dv_write_dif_id(dv_sect_vaux, chan, i, j, buf);
                buf += dv_write_pack(dv_video_source,  c, buf);
                buf += dv_write_pack(dv_video_control, c, buf);
                buf += 7*5;
                buf += dv_write_pack(dv_video_source,  c, buf);
                buf += dv_write_pack(dv_video_control, c, buf);
                buf += 4*5 + 2;
            }


            for (j = 0; j < 135; j++) {
                if (j%15 == 0) {
                    memset(buf, 0xff, 80);
                    buf += dv_write_dif_id(dv_sect_audio, chan, i, j/15, buf);
                    buf += 77;
                }
                buf += dv_write_dif_id(dv_sect_video, chan, i, j, buf);
                buf += 77;


            }
        }
    }
}
