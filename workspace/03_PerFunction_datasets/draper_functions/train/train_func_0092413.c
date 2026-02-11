id3tag_set_textinfo_ucs2(lame_global_flags * gfp, char const *id, unsigned short const *text)
{
    uint32_t const t_mask = FRAME_ID('T', 0, 0, 0);
    uint32_t const frame_id = toID3v2TagId(id);
    if (frame_id == 0) {
        return -1;
    }
    if ((frame_id & t_mask) == t_mask) {
        if (isNumericString(frame_id)) {
            return -2;
        }
        if (text == 0) {
            return 0;
        }
        if (!hasUcs2ByteOrderMarker(text[0])) {
            return -3;
        }
        if (gfp != 0) {
            if (frame_id == ID_TXXX) {
                return id3tag_set_userinfo_ucs2(gfp->internal_flags, text);
            }
            return id3v2_add_ucs2(gfp->internal_flags, frame_id, 0, 0, text);
        }
    }
    return -255;
}
