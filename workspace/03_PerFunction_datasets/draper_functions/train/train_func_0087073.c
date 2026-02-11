read_x3f_prop_header(FILE *inptr,unsigned short byteorder,unsigned long offset)
{
    static struct x3f_prop_header header;
    struct x3f_prop_header *headerptr = (struct x3f_prop_header *)0;

    if(!feof(inptr) && !ferror(inptr))
    {
        header.section_id = read_ulong(inptr,byteorder,offset);
        header.version_minor = read_ushort(inptr,byteorder,HERE);
        header.version_major = read_ushort(inptr,byteorder,HERE);
        header.num_entries = read_ulong(inptr,byteorder,HERE);
        header.char_format = read_ulong(inptr,byteorder,HERE);
        header.reserved = read_ulong(inptr,byteorder,HERE);
        header.entry_length = read_ulong(inptr,byteorder,HERE);
        if(!feof(inptr) && !ferror(inptr))
            headerptr = &header;
    }
    return(headerptr);
}
