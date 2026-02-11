id3v22_read_image (VFSFile * handle, void * * image_data,
 int64_t * image_size64)
{
    int version, header_size, data_size, parsed, image_size = 0;
    bool_t syncsafe;
    gsize offset;
    bool_t found = FALSE;

    if (! read_header (handle, & version, & syncsafe, & offset, & header_size,
     & data_size))
        return FALSE;

    for (parsed = 0; parsed < data_size && ! found; )
    {
        int frame_size, size, type;
        char key[5];
        unsigned char * data;
        char * mime;
        int frame_length;

        if (! read_frame (handle, data_size - parsed, version, syncsafe,
         & frame_size, key, & data, & size))
            break;

        frame_length = size;

        if (! strcmp (key, "PIC") && parse_pic (data, frame_length, & mime, & type,
         image_data, & image_size))
        {
            g_free (mime);

            if (type == 3)
                found = TRUE;
            else if (type == 0)
                found = TRUE;
            else if (*image_data != NULL)
            {
                g_free(*image_data);
                *image_data = NULL;
            }
        }

        g_free (data);
        parsed += frame_size;
    }

    if (found)
        * image_size64 = image_size;

    return found;
}
