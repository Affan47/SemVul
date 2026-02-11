hashfloat4(PG_FUNCTION_ARGS)
{
	float4		key = PG_GETARG_FLOAT4(0);
	float8		key8;


	if (key == (float4) 0)
		PG_RETURN_UINT32(0);


	key8 = key;

	return hash_any((unsigned char *) &key8, sizeof(key8));
}
