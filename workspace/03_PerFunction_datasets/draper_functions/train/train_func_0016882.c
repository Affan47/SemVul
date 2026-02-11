vesacon_load_background(const char *filename)
{
    FILE *fp = NULL;
    uint8_t header[8];
    int rv = 1;

    if (__vesacon_pixel_format == PXF_NONE)
	return 0;

    fp = fopen(filename, "r");

    if (!fp)
	goto err;

    if (fread(header, 1, 8, fp) != 8)
	goto err;

    if (!png_sig_cmp(header, 0, 8)) {
	rv = read_png_file(fp);
    } else if (!jpeg_sig_cmp(header, 8)) {
	rv = read_jpeg_file(fp, header, 8);
    } else if (!lss16_sig_cmp(header, 8)) {
	rv = read_lss16_file(fp, header, 8);
    }


    draw_background();

err:
    if (fp)
	fclose(fp);

    return rv;
}
