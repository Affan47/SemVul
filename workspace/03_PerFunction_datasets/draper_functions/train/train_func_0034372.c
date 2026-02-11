ps_rle_encode (PSL_LONG *nbytes, unsigned char *input)
{


	PSL_LONG count = 0, out = 0, in = 0, i;
	unsigned char pixel, *output;

	i = MAX (512, *nbytes) + 136;
	output = (unsigned char *)ps_memory (VNULL, (size_t)i, sizeof (unsigned char));


	while (count < *nbytes && (out < in || out < 512)) {
		in = count;
		pixel = input[in++];
		while (in < *nbytes && in - count < 127 && input[in] == pixel) in++;
		if (in - count == 1) {
			while (in < *nbytes && (in - count) < 127 && ((input[in] != input[in-1] || in > 1) && input[in] != input[in-2])) in++;
			while (in < *nbytes && input[in] == input[in-1]) in--;
			output[out++] = (unsigned char)(in - count - 1);
			for (i = count; i < in; i++) output[out++] = input[i];
		}
		else {
			output[out++] = (unsigned char)(count - in + 1);
			output[out++] = pixel;
		}
		count = in;
	}


	output[out++] = 128;


	if (out > in) {
		if (PSL->internal.verbose) fprintf (stderr, "pslib: RLE inflated %ld to %ld bytes. No compression done.\n", in, out);
		ps_free (output);
		return (NULL);
	}


	if (PSL->internal.verbose) fprintf (stderr, "pslib: RLE compressed %ld to %ld bytes\n", in, out);
	*nbytes = out;
	return (output);
}
