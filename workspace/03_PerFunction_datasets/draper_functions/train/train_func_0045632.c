gsf_output_inc_cur_offset (GsfOutput *output, gsf_off_t num_bytes)
{
	output->cur_offset += num_bytes;
	if (output->cur_offset < num_bytes)
		return gsf_output_set_error (output, 0, "Output size overflow.");
	if (output->cur_size < output->cur_offset)
		output->cur_size = output->cur_offset;
	return TRUE;
}
