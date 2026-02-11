parse_header(struct pio_bed_file_t *bed_file)
{
    unsigned char header[ BED_HEADER_MAX_SIZE ];
    if( fread( header, 1, BED_HEADER_MAX_SIZE, bed_file->fp ) != BED_HEADER_MAX_SIZE )
    {
        return PIO_ERROR;
    }

    bed_header_from_bytes( &bed_file->header, header );

    fseek( bed_file->fp, bed_header_data_offset( &bed_file->header ), SEEK_SET );

    return PIO_OK;
}
