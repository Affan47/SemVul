CRYPTO_dup_ex_data(int class_index, CRYPTO_EX_DATA *to,
	     CRYPTO_EX_DATA *from)
	{
	IMPL_CHECK
	return EX_IMPL(dup_ex_data)(class_index, to, from);
	}
