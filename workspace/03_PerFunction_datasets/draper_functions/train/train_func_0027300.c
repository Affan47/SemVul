mjpg_init(struct ng_video_fmt *fmt)
{
    struct mjpeg_compress *h;

    h = malloc(sizeof(*h));
    if (NULL == h)
	return NULL;
    memset(h,0,sizeof(*h));

    h->mjpg_cinfo.err = jpeg_std_error(&h->mjpg_jerr);
    jpeg_create_compress(&h->mjpg_cinfo);

    h->mjpg_dest.init_destination    = mjpg_dest_init;
    h->mjpg_dest.empty_output_buffer = mjpg_dest_flush;
    h->mjpg_dest.term_destination    = mjpg_dest_term;
    h->mjpg_cinfo.dest               = &h->mjpg_dest;

    h->fmt = *fmt;
    h->mjpg_tables = TRUE;
    h->mjpg_cinfo.image_width  =  fmt->width;
    h->mjpg_cinfo.image_height =  fmt->height;

    h->mjpg_cinfo.image_width  &= ~(2*DCTSIZE-1);
    h->mjpg_cinfo.image_height &= ~(2*DCTSIZE-1);

    return h;
}
