pcx_increment_load_data_4(struct pcx_context *context)
{
	guint i;
	guchar *planes[1];
	guint line_bytes;

	planes[0] = context->line;

	while(read_scanline_data(context->buf, context->buf_pos, planes, 1, context->num_planes, context->bytesperline, &line_bytes)) {
		pcx_chop_context_buf(context, line_bytes);

		for(i = 0; i < context->width; i++) {
			guchar p;

			p = read_pixel_4(planes[0], i) & 0xf;
			context->data[context->current_line * context->rowstride + i * 3 + 0] = context->header->palette[p * 3 + 0];
			context->data[context->current_line * context->rowstride + i * 3 + 1] = context->header->palette[p * 3 + 1];
			context->data[context->current_line * context->rowstride + i * 3 + 2] = context->header->palette[p * 3 + 2];
		}

		if(context->updated_func)
			context->updated_func(context->pixbuf, 0, context->current_line, context->width, 1, context->user_data);

		context->current_line++;

		if(context->current_line == context->height) {
			context->current_task = PCX_TASK_DONE;
			return TRUE;
		}
	}

	return TRUE;
}
