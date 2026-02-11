type_maximum_size(Oid type_oid, int32 typemod)
{
	if (typemod < 0)
		return -1;

	switch (type_oid)
	{
		case BPCHAROID:
		case VARCHAROID:


			return (typemod - VARHDRSZ) *
				pg_encoding_max_length(GetDatabaseEncoding())
				+ VARHDRSZ;

		case NUMERICOID:
			return numeric_maximum_size(typemod);

		case VARBITOID:
		case BITOID:

			return (typemod + (BITS_PER_BYTE - 1)) / BITS_PER_BYTE
				+ 2 * sizeof(int32);
	}


	return -1;
}
