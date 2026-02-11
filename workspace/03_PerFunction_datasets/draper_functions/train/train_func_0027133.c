gif_get_frame_info (GifContext *context)
{
	unsigned char buf[9];

	if (!gif_read (context, buf, 9)) {
		return -1;
	}


	context->frame_len = LM_to_uint (buf[4], buf[5]);
	context->frame_height = LM_to_uint (buf[6], buf[7]);
	context->x_offset = LM_to_uint (buf[0], buf[1]);
	context->y_offset = LM_to_uint (buf[2], buf[3]);

	if (context->animation->frames == NULL &&
            context->gif89.disposal == 3) {


                context->gif89.disposal = 0;
	}

	context->frame_interlace = BitSet (buf[8], INTERLACE);

#ifdef DUMP_IMAGE_DETAILS
        g_print (">width: %d height: %d xoffset: %d yoffset: %d disposal: %d delay: %d transparent: %d interlace: %d\n",
                 context->frame_len, context->frame_height, context->x_offset, context->y_offset,
                 context->gif89.disposal, context->gif89.delay_time, context->gif89.transparent, context->frame_interlace);
#endif

	if (BitSet (buf[8], LOCALCOLORMAP)) {

#ifdef DUMP_IMAGE_DETAILS
                g_print (">has local colormap\n");
#endif


                context->frame_cmap_active = TRUE;
		context->frame_bit_pixel = 1 << ((buf[8] & 0x07) + 1);
		gif_set_get_colormap2 (context);
		return 0;
	}

        if (!context->has_global_cmap) {
                context->state = GIF_DONE;

                g_set_error_literal (context->error,
                                     GDK_PIXBUF_ERROR,
                                     GDK_PIXBUF_ERROR_CORRUPT_IMAGE,
                                     _("GIF image has no global colormap, and a frame inside it has no local colormap."));

		return -2;
        }

	gif_set_prepare_lzw (context);
	return 0;

}
