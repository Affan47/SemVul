mar_parse_app (PJDEC_INST g, UINT marker)
{
    UINT len;
    BYTE id1, id2, id3;

    len = read_uint (g);
    if (len <= 5) {

        read_skip_forward (g, len-2);
        return;
    }

    id1 = read_byte (g);
    id2 = read_byte (g);
    id3 = read_byte (g);
    read_skip_backward (g, 5);

    if (marker==MARKER_APP+1 && id1==0x47 && id2==0x33 && id3==0x46) {

        parse_app_g3fax (g);
    } else if (marker==MARKER_APP+0 && (id1=='J' || id1=='j')
               && (id2=='F' || id2=='f') && (id3=='I' || id3=='i')) {

        parse_app_jfif (g);
    } else if (marker==MARKER_APP+1 && len==18) {

        parse_app_short_header (g);
    } else {

        read_skip_forward (g, len);
    }
}
