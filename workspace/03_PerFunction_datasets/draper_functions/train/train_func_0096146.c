_af_print_audioformat (AudioFormat *fmt)
{

	printf("{ %7.2f Hz %d ch ", fmt->sampleRate, fmt->channelCount);


	switch (fmt->sampleFormat)
	{
		case AF_SAMPFMT_TWOSCOMP:
			printf("%db 2 ", fmt->sampleWidth);
			break;
		case AF_SAMPFMT_UNSIGNED:
			printf("%db u ", fmt->sampleWidth);
			break;
		case AF_SAMPFMT_FLOAT:
			printf("flt ");
			break;
		case AF_SAMPFMT_DOUBLE:
			printf("dbl ");
			break;
		default:
			printf("%dsampfmt? ", fmt->sampleFormat);
	}


	printf("(%.30g+-%.30g [%.30g,%.30g]) ",
		fmt->pcm.intercept, fmt->pcm.slope,
		fmt->pcm.minClip, fmt->pcm.maxClip);


	switch (fmt->byteOrder)
	{
		case AF_BYTEORDER_BIGENDIAN:
			printf("big ");
			break;
		case AF_BYTEORDER_LITTLEENDIAN:
			printf("little ");
			break;
		default:
			printf("%dbyteorder? ", fmt->byteOrder);
			break;
	}


	{
		const CompressionUnit *unit = _af_compression_unit_from_id(fmt->compressionType);
		if (!unit)
			printf("%dcompression?", fmt->compressionType);
		else if (fmt->compressionType == AF_COMPRESSION_NONE)
			printf("pcm");
		else
			printf("%s", unit->label);
	}

	printf(" }");
}
