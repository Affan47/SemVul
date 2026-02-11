bn_write_be(const bignum256 *in_number, uint8_t *out_number)
{
	int i;
	uint32_t temp = in_number->val[8] << 16;
	for (i = 0; i < 8; i++) {

		uint32_t limb = in_number->val[7 - i];
		temp |= limb >> (14 - 2*i);
		write_be(out_number + i * 4, temp);
		temp = limb << (18 + 2*i);
	}
}
