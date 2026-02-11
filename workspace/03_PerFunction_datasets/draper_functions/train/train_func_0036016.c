zmod_poly_mul_middle_precache(zmod_poly_t output, zmod_poly_t input1,
                                        zmod_poly_precache_t pre, unsigned long trunc)
{
	zmod_poly_t temp;

	ulong length = FLINT_MIN(input1->length + pre->length2 - 1, trunc);

	if (input1 == output)
	{
		zmod_poly_init2(temp, input1->p, length);
		_zmod_poly_mul_KS_middle_precache(temp, input1, pre, 0, trunc);
		zmod_poly_swap(temp, output);
		zmod_poly_clear(temp);
	} else
	{
		zmod_poly_fit_length(output, length);
	   _zmod_poly_mul_KS_middle_precache(output, input1, pre, 0, trunc);
	}
}
