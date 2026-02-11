concatenate_primary_alpha(jxr_image_t image, FILE *fpPrimary, FILE *fpAlpha)
{
    context *con = (context*) jxr_get_user_data(image);
    if (con->file==0)
    {
        set_pad_bytes(con, image);

        con->alpha = 1;
        start_output_file(con, jxr_get_EXTENDED_IMAGE_WIDTH(image), jxr_get_EXTENDED_IMAGE_HEIGHT(image),
            jxr_get_IMAGE_WIDTH(image), jxr_get_IMAGE_HEIGHT(image),
            jxr_get_IMAGE_CHANNELS(image) + 1, jxr_get_OUTPUT_BITDEPTH(image), jxr_get_pixel_format(image));
    }
    fseek(fpPrimary, 0, SEEK_END);
    long size = ftell(fpPrimary);
    fseek(fpPrimary, 0, SEEK_SET);
    long i;
    for(i = 0; i < size; i++)
    {
        uint8_t val;
        fread(&val, 1, 1, fpPrimary);
        fwrite(&val, 1, 1, con->file);
    }
    fseek(fpAlpha, 0, SEEK_END);
    size = ftell(fpAlpha);
    fseek(fpAlpha, 0, SEEK_SET);
    for(i = 0; i < size; i++)
    {
        uint8_t val;
        fread(&val, 1, 1, fpAlpha);
        fwrite(&val, 1, 1, con->file);
    }
}
