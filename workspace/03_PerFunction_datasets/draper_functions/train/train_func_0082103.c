_get_id3v2_trackno(const char *frame_data, unsigned int frame_size, struct id3_info *info, lms_charset_conv_t *cs_conv)
{
    struct lms_string_size trackno = { };

    _get_id3v2_frame_info(frame_data, frame_size, &trackno, cs_conv, 0);
    if (!trackno.str)
        return;
    info->trackno = atoi(trackno.str);
    free(trackno.str);
}
