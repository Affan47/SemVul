decompress_jpeg_image_from_file(const char *pSrc_filename, int *width, int *height, int *actual_comps, int req_comps)
{
    jpgd::jpeg_decoder_file_stream file_stream;
    if (!file_stream.open(pSrc_filename))
        return NULL;
    return decompress_jpeg_image_from_stream(&file_stream, width, height, actual_comps, req_comps);
}
