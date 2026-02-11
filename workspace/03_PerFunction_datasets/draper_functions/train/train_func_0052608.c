compress_image_to_jpeg_file(const char *pFilename, int width, int height, int num_channels, const uint8 *pImage_data, const params &comp_params)
{
    cfile_stream dst_stream;
    if (!dst_stream.open(pFilename))
        return false;

    compress_image_to_stream(dst_stream, width, height, num_channels, pImage_data, comp_params);

    return dst_stream.close();
}
