fill_pcx_context(struct pcx_context *context)
{
	struct pcx_header *header = context->header;

	context->bpp = header->bitsperpixel;
	context->width = header->xmax - header->xmin + 1;
	context->height = header->ymax - header->ymin + 1;
	context->num_planes = header->colorplanes;
	context->bytesperline = header->bytesperline;

	if(header->version == 5 && context->bpp == 8 && context->num_planes == 3)
		context->bpp = 24;
}
