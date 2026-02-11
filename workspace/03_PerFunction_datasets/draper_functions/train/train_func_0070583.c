bert_decode_float(bert_decoder_t *decoder,bert_data_t **data)
{
	char float_buffer[32];
	int result;

	memset(float_buffer,'\0',sizeof(unsigned char)*32);

	if ((result = bert_decode_bytes((unsigned char *)float_buffer,decoder,31)) != BERT_SUCCESS)
	{
		return result;
	}

	double floating_point;

	if (sscanf(float_buffer,"%lf",&floating_point) != 1)
	{
		return BERT_ERRNO_INVALID;
	}

	bert_data_t *new_data;

	if (!(new_data = bert_data_create_float(floating_point)))
	{
		return BERT_ERRNO_MALLOC;
	}

	*data = new_data;
	return BERT_SUCCESS;
}
