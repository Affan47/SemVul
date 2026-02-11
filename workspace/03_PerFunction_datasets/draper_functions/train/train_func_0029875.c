_read_block(BLURAY *bd, BD_STREAM *st, uint8_t *buf)
{
    const size_t len = 6144;

    if (st->fp) {
        BD_DEBUG(DBG_STREAM, "Reading unit at %"PRIu64"...\n", st->clip_block_pos);

        if (len + st->clip_block_pos <= st->clip_size) {
            size_t read_len;

            if ((read_len = file_read(st->fp, buf, len))) {
                if (read_len != len) {
                    BD_DEBUG(DBG_STREAM | DBG_CRIT, "Read %d bytes at %"PRIu64" ; requested %d !\n", (int)read_len, st->clip_block_pos, (int)len);
                }
                if (bd->libaacs && libaacs_decrypt_unit(bd->libaacs, buf)) {
                    _queue_event(bd, BD_EVENT_ENCRYPTED, BD_ERROR_AACS);
                    return -1;
                }
                if (st->bdplus && (libbdplus_fixup(st->bdplus, buf, len) < 0)) {
                    _queue_event(bd, BD_EVENT_ENCRYPTED, BD_ERROR_BDPLUS);
                }

                st->clip_block_pos += len;


                if (buf[0] & 0xc0) {

                    if (buf[4] != 0x47 || buf[4+192] != 0x47 || buf[4+2*192] != 0x47) {
                        BD_DEBUG(DBG_BLURAY | DBG_CRIT,
                                 "TP header copy permission indicator != 0, unit is still encrypted?\n");
                        _queue_event(bd, BD_EVENT_ENCRYPTED, BD_ERROR_AACS);
                        return -1;
                    }
                }

                if (st->m2ts_filter) {
                    int result = m2ts_filter(st->m2ts_filter, buf);
                    if (result < 0) {
                        m2ts_filter_close(&st->m2ts_filter);
                        BD_DEBUG(DBG_BLURAY | DBG_CRIT, "m2ts filter error\n");
                    }
                }

                BD_DEBUG(DBG_STREAM, "Read unit OK!\n");

#ifdef BLURAY_READ_ERROR_TEST

                if (random() % 1000)
#else
                return 1;
#endif
            }

            BD_DEBUG(DBG_STREAM | DBG_CRIT, "Read unit at %"PRIu64" failed !\n", st->clip_block_pos);

            _queue_event(bd, BD_EVENT_READ_ERROR, 0);


            st->clip_block_pos += len;
            st->clip_pos += len;

            if (file_seek(st->fp, st->clip_block_pos, SEEK_SET) < 0) {
                BD_DEBUG(DBG_BLURAY | DBG_CRIT, "Unable to seek clip %s!\n", st->clip->name);
            }

            return 0;
        }

        BD_DEBUG(DBG_STREAM | DBG_CRIT, "Read past EOF !\n");


        st->clip_block_pos += len;
        st->clip_pos += len;

        return 0;
    }

    BD_DEBUG(DBG_BLURAY, "No valid title selected!\n");

    return -1;
}
