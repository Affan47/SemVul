cram_byte_array_len_decode(cram_slice *slice, cram_codec *c,
			       cram_block *in, char *out,
			       int *out_size) {

    int32_t len, one = 1;

    c->byte_array_len.len_codec->decode(slice, c->byte_array_len.len_codec, in, (char *)&len, &one);


    if (c->byte_array_len.value_codec) {
	c->byte_array_len.value_codec->decode(slice,
					      c->byte_array_len.value_codec,
					      in, out, &len);
    } else {
	return -1;
    }

    *out_size = len;

    return 0;
}
