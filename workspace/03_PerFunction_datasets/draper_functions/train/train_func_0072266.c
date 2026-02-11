silence_generator_generate(struct ast_channel *chan, void *data, int len, int samples)
{
	short buf[samples];
	struct ast_frame frame = {
		.frametype = AST_FRAME_VOICE,
		.data.ptr = buf,
		.samples = samples,
		.datalen = sizeof(buf),
	};
	ast_format_set(&frame.subclass.format, AST_FORMAT_SLINEAR, 0);

	memset(buf, 0, sizeof(buf));

	if (ast_write(chan, &frame))
		return -1;

	return 0;
}
