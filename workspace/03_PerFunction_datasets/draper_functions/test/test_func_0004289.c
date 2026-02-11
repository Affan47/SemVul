mjpg_bgr_compress(struct jpeg_compress_struct* mjpg_cinfo,
		      unsigned char *d, const unsigned char *s, int p)
{
    int i;
    const unsigned char *line;
    unsigned char* hb;
    mjpg_client* mc = (mjpg_client*) mjpg_cinfo->client_data;

    if (debug > 1)
	fprintf(stderr,"mjpg_rgb_compress\n");

    mc->mjpg_buffer  = d;
    mc->mjpg_bufsize = 3*mjpg_cinfo->image_width*mjpg_cinfo->image_height;
    hb = d + mc->mjpg_bufsize;
    jpeg_start_compress(mjpg_cinfo, mc->mjpg_tables);
    if (!mc->invert_direction)
	for (i = 0, line = s; i < mjpg_cinfo->image_height;
	     i++, line += 3*mjpg_cinfo->image_width)
	{


            memcpy(hb, line, mjpg_cinfo->image_width * 3);
	    jpeg_write_scanlines(mjpg_cinfo, &hb, 1);
	}
    else
	for (i = 0, line = s + mc->mjpg_bufsize-3*mjpg_cinfo->image_width;
	     i < mjpg_cinfo->image_height;
	     i++, line -= 3*mjpg_cinfo->image_width)
	{
	    bgr2rgb(hb, line, mjpg_cinfo->image_width);
	    jpeg_write_scanlines(mjpg_cinfo, &hb, 1);
	}

    jpeg_finish_compress(mjpg_cinfo);
    mc->mjpg_tables = FALSE;

    return mc->mjpg_bufused;
}
