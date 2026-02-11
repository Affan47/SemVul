bn2heim_int(BIGNUM *bn, heim_integer *integer)
{
    integer->length = BN_num_bytes(bn);
    integer->data = malloc(integer->length);
    if (integer->data == NULL) {
	integer->length = 0;
	return ENOMEM;
    }
    BN_bn2bin(bn, integer->data);
    integer->negative = BN_is_negative(bn);
    return 0;
}
