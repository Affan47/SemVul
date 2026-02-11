bert_decode_small_bignum(bert_decoder_t *decoder,bert_data_t **data)
{
	int result;
	uint8_t i;

	if ((result = bert_decode_uint8(decoder,&i)) != BERT_SUCCESS)
	{
		return result;
	}

	return bert_decode_bignum(decoder,data,i);
}
