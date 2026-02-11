pl_base64_encode_buffer (PLBase64Encoder *data, const unsigned char *in,
			 PRUint32 size)
{
    const unsigned char *end = in + size;
    char *out = data->output_buffer + data->output_length;
    unsigned int i = data->in_buffer_count;
    PRUint32 n = 0;
    int off;
    PRUint32 output_threshold;


    if (size < (3 - i)) {
	data->in_buffer[i++] = in[0];
	if (size > 1)
	    data->in_buffer[i++] = in[1];
	PR_ASSERT(i < 3);
	data->in_buffer_count = i;
	return PR_SUCCESS;
    }


    if (i > 0) {
	n = data->in_buffer[0];
	if (i > 1)
	    n = (n << 8) | data->in_buffer[1];
	data->in_buffer_count = 0;
    }


    off = (size + i) % 3;
    if (off > 0) {
	size -= off;
	data->in_buffer[0] = in[size];
	if (off > 1)
	    data->in_buffer[1] = in[size + 1];
	data->in_buffer_count = off;
	end -= off;
    }

    output_threshold = data->output_buflen - 3;


    while (in < end) {
	int j, k;

	while (i < 3) {
	    n = (n << 8) | *in++;
	    i++;
	}
	i = 0;

	if (data->line_length > 0) {
	    if (data->current_column >= data->line_length) {
		data->current_column = 0;
		*out++ = B64_CR;
		*out++ = B64_LF;
		data->output_length += 2;
	    }
	    data->current_column += 4;
	}

	for (j = 18; j >= 0; j -= 6) {
	    k = (n >> j) & 0x3F;
	    *out++ = base64_valuetocode[k];
	}
	n = 0;
	data->output_length += 4;

	if (data->output_length >= output_threshold) {
	    PR_ASSERT(data->output_length <= data->output_buflen);
	    if (data->output_fn != NULL) {
		PRInt32 output_result;

		output_result = data->output_fn (data->output_arg,
						 data->output_buffer,
						 (PRInt32) data->output_length);
		if (output_result < 0)
		    return PR_FAILURE;

		out = data->output_buffer;
		data->output_length = 0;
	    } else {


		PR_ASSERT(in == end);
		if (in < end) {
		    PR_SetError (PR_BUFFER_OVERFLOW_ERROR, 0);
		    return PR_FAILURE;
		}
	    }
	}
    }

    return PR_SUCCESS;
}
