id3v24_read_tag (Tuple * tuple, VFSFile * handle)
{
    int version, header_size, data_size, footer_size;
    bool_t syncsafe;
    int64_t offset;
    int pos;

    if (! read_header (handle, & version, & syncsafe, & offset, & header_size,
     & data_size, & footer_size))
        return FALSE;

    for (pos = 0; pos < data_size; )
    {
        int frame_size, size, id;
        char key[5];
        unsigned char * data;

        if (! read_frame (handle, data_size - pos, version, syncsafe,
         & frame_size, key, & data, & size))
            break;

        id = get_frame_id (key);

        switch (id)
        {
          case ID3_ALBUM:
            associate_string (tuple, FIELD_ALBUM, NULL, data, size);
            break;
          case ID3_TITLE:
            associate_string (tuple, FIELD_TITLE, NULL, data, size);
            break;
          case ID3_COMPOSER:
            associate_string (tuple, FIELD_COMPOSER, NULL, data, size);
            break;
          case ID3_COPYRIGHT:
            associate_string (tuple, FIELD_COPYRIGHT, NULL, data, size);
            break;
          case ID3_DATE:
            associate_string (tuple, FIELD_DATE, NULL, data, size);
            break;
          case ID3_LENGTH:
            associate_int (tuple, FIELD_LENGTH, NULL, data, size);
            break;
          case ID3_ARTIST:
            associate_string (tuple, FIELD_ARTIST, NULL, data, size);
            break;
          case ID3_TRACKNR:
            associate_int (tuple, FIELD_TRACK_NUMBER, NULL, data, size);
            break;
          case ID3_YEAR:
          case ID3_RECORDING_TIME:
            associate_int (tuple, FIELD_YEAR, NULL, data, size);
            break;
          case ID3_GENRE:
            decode_genre (tuple, data, size);
            break;
          case ID3_COMMENT:
            decode_comment (tuple, data, size);
            break;
          case ID3_PRIVATE:
            decode_private_info (tuple, data, size);
            break;
          case ID3_RVA2:
            decode_rva2 (tuple, data, size);
            break;
          default:
            TAGDBG ("Ignoring unsupported ID3 frame %s.\n", key);
            break;
        }

        g_free (data);
        pos += frame_size;
    }

    return TRUE;
}
