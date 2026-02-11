gsf_input_textline_new (GsfInput *source)
{
	GsfInputTextline *input;

	g_return_val_if_fail (source != NULL, NULL);

	input = g_object_new (GSF_INPUT_TEXTLINE_TYPE, NULL);
	input->source = g_object_ref (source);
	input->buf = NULL;
	input->buf_size = 0;
	gsf_input_set_size (GSF_INPUT (input), gsf_input_size (source));
	gsf_input_set_name (GSF_INPUT (input), gsf_input_name (source));

	return GSF_INPUT (input);
}
