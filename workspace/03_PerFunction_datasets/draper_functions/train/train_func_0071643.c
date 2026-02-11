TestBlockBias(CuTest* tc)
{

	struct ByteBlock input;
	memcpy(&input, &test_input, sizeof(input));
	struct FloatBlock output;

	float bias_amount = -128.0f;
	byteblock_add(&input, bias_amount, &output);

	for (int y=0;y<size;y++) {
		for (int x=0;x<size;x++) {
			CuAssertTrue(tc, (float)input.data[y][x] > output.data[y][x]);
			CuAssertTrue(tc, output.data[y][x] - (float)input.data[y][x] == bias_amount);
		}
	}
}
