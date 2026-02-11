_parse_id3v2_frame(struct id3v2_frame_header *fh, const char *frame_data, struct id3_info *info, lms_charset_conv_t **cs_convs)
{
    lms_charset_conv_t *cs_conv;
    unsigned int text_encoding, frame_size;
    const char *fid;


    if (fh->frame_size <= 1)
        return;

#if 0
    fprintf(stderr, "frame id = %.4s frame size = %d text encoding = %d\n",
            fh->frame_id, fh->frame_size, frame_data[0]);
#endif

    fid = fh->frame_id;

    if (fid[0] == 'A' && fid[1] == 'P' && fid[2] == 'I' && fid[3] == 'C') {
        _get_id3v2_cover_art (frame_data, fh->frame_size, info);
    }


    if (fid[0] != 'T')
        return;


    text_encoding = frame_data[0];


    frame_data += 1;
    frame_size = fh->frame_size - 1;

    if (text_encoding < ID3_NUM_ENCODINGS) {
        if (text_encoding == ID3_ENCODING_UTF16) {

            if (frame_size <= 2)
                return;

            if (memcmp(frame_data, "\xfe\xff", 2) == 0)
                text_encoding = ID3_ENCODING_UTF16BE;
            else
                text_encoding = ID3_ENCODING_UTF16LE;
            frame_data += 2;
            frame_size -= 2;
        }
        cs_conv = cs_convs[text_encoding];
    } else
        cs_conv = NULL;


    if ((fid[1] == 'T' && fid[2] == '2') ||
        (fid[1] == 'I' && fid[2] == 'T' && fid[3] == '2'))
        _get_id3v2_frame_info(frame_data, frame_size, &info->title, cs_conv, 1);
    else if (fid[1] == 'P') {
        if (fid[2] == 'E')
            _get_id3v2_artist(fid[3] - '1', frame_data, frame_size,
                              info, cs_conv);
        else if (fid[2] >= '1' && fid[2] <= '4')
            _get_id3v2_artist(fid[2] - '1', frame_data, frame_size,
                              info, cs_conv);
    }

    else if (fid[1] == 'A' && fid[2] == 'L')
        _get_id3v2_frame_info(frame_data, frame_size, &info->album, cs_conv, 1);

    else if (fid[1] == 'C' && fid[2] == 'O' && fid[3] == 'N')
        _get_id3v2_genre(frame_data, frame_size, &info->genre, cs_conv);
    else if (fid[1] == 'R' && (fid[2] == 'K' ||
                               (fid[2] == 'C' && fid[3] == 'K')))
        _get_id3v2_trackno(frame_data, frame_size, info, cs_conv);
}
