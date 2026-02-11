bert_encode_boolean(bert_encoder_t *encoder,unsigned int boolean)
{
	if (boolean == 1)
	{
		return bert_encode_true(encoder);
	}
	else if (boolean == 0)
	{
		return bert_encode_false(encoder);
	}

	return BERT_ERRNO_INVALID;
}
