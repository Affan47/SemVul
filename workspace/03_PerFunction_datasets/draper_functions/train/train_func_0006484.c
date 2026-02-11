test_output()
{
	if (output[0] != BERT_MAGIC)
	{
		test_fail("bert_encoder_push did not add the magic byte");
	}

	if (output[1] != BERT_STRING)
	{
		test_fail("bert_encoder_push did not add the SMALL_STRING magic byte");
	}

	if (output[5] != EXPECTED_LENGTH)
	{
		test_fail("bert_encoder_push encoded %u as the atom length, expected %u",output[5],EXPECTED_LENGTH);
	}

	test_strings((const char *)(output+6),EXPECTED,EXPECTED_LENGTH);
}
