ape_find_header (VFSFile * handle, APEHeader * header, int *
 start, int * length, int * data_start, int * data_length)
{
    APEHeader secondary;

    if (vfs_fseek (handle, 0, SEEK_SET))
        return FALSE;

    if (ape_read_header (handle, header))
    {
        TAGDBG ("Found header at 0, length = %d, version = %d.\n", (int)
         header->length, (int) header->version);
        * start = 0;
        * length = header->length;
        * data_start = sizeof (APEHeader);
        * data_length = header->length - sizeof (APEHeader);

        if (! (header->flags & APE_FLAG_HAS_HEADER) || ! (header->flags &
         APE_FLAG_IS_HEADER))
        {
            TAGDBG ("Invalid header flags (%u).\n", (unsigned int) header->flags);
            return FALSE;
        }

        if (! (header->flags & APE_FLAG_HAS_NO_FOOTER))
        {
            if (vfs_fseek (handle, header->length, SEEK_CUR))
                return FALSE;

            if (! ape_read_header (handle, & secondary))
            {
                TAGDBG ("Expected footer, but found none.\n");
                return FALSE;
            }

            * length += sizeof (APEHeader);
        }

        return TRUE;
    }

    if (vfs_fseek (handle, -(int) sizeof (APEHeader), SEEK_END))
        return FALSE;

    if (ape_read_header (handle, header))
    {
        TAGDBG ("Found footer at %d, length = %d, version = %d.\n", (int)
         vfs_ftell (handle) - (int) sizeof (APEHeader), (int) header->length,
         (int) header->version);
        * start = vfs_ftell (handle) - header->length;
        * length = header->length;
        * data_start = vfs_ftell (handle) - header->length;
        * data_length = header->length - sizeof (APEHeader);

        if ((header->flags & APE_FLAG_HAS_NO_FOOTER) || (header->flags &
         APE_FLAG_IS_HEADER))
        {
            TAGDBG ("Invalid footer flags (%u).\n", (unsigned int) header->flags);
            return FALSE;
        }

        if (header->flags & APE_FLAG_HAS_HEADER)
        {
            if (vfs_fseek (handle, -(int) header->length - sizeof (APEHeader),
             SEEK_CUR))
                return FALSE;

            if (! ape_read_header (handle, & secondary))
            {
                TAGDBG ("Expected header, but found none.\n");
                return FALSE;
            }

            * start -= sizeof (APEHeader);
            * length += sizeof (APEHeader);
        }

        return TRUE;
    }

    TAGDBG ("No header found.\n");
    return FALSE;
}
