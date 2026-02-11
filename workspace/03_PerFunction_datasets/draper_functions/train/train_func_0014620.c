decompress_jpeg_image_from_memory(const unsigned char *pSrc_data, int src_data_size, int *width, int *height, int *actual_comps, int req_comps)
{
    jpgd::jpeg_decoder_mem_stream mem_stream(pSrc_data, src_data_size);
    return decompress_jpeg_image_from_stream(&mem_stream, width, height, actual_comps, req_comps);
}
