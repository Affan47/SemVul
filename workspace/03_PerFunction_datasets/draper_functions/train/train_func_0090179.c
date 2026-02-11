alloc_importfile(
        msft_typelib_t *typelib,
        int guidoffset,
        int major_version,
        int minor_version,
        const char *filename)
{
    int length;
    int offset;
    MSFT_ImpFile *importfile;
    char *encoded_string;

    length = ctl2_encode_string(filename, &encoded_string);

    encoded_string[0] <<= 2;
    encoded_string[0] |= 1;

    for (offset = 0; offset < typelib->typelib_segdir[MSFT_SEG_IMPORTFILES].length;
	 offset += (((typelib->typelib_segment_data[MSFT_SEG_IMPORTFILES][offset + 0xd] << 8) |
	              typelib->typelib_segment_data[MSFT_SEG_IMPORTFILES][offset + 0xc]) >> 2) + 0xc) {
	if (!memcmp(encoded_string, typelib->typelib_segment_data[MSFT_SEG_IMPORTFILES] + offset + 0xc, length)) return offset;
    }

    offset = ctl2_alloc_segment(typelib, MSFT_SEG_IMPORTFILES, length + 0xc, 0);

    importfile = (MSFT_ImpFile *)&typelib->typelib_segment_data[MSFT_SEG_IMPORTFILES][offset];
    importfile->guid = guidoffset;
    importfile->lcid = typelib->typelib_header.lcid2;
    importfile->version = major_version | (minor_version << 16);
    memcpy(&importfile->filename, encoded_string, length);

    return offset;
}
