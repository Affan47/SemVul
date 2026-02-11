IoBigNum_mul(IoBigNum * self, IoObject * locals, IoMessage * m)
{
	IoBigNum *result = IoBigNum_new(IOSTATE);
	IoObject *other = IoMessage_locals_valueArgAt_(m, locals, 0);
	if (ISNUMBER(other))
		mpz_mul_si(DATA(result)->integer, DATA(self)->integer, IoNumber_asLong(other));
	else if (ISBIGNUM(other))
		mpz_mul(DATA(result)->integer, DATA(self)->integer, DATA(other)->integer);
	else
		IoState_error_(IOSTATE, m, "argument 0 to method '%s' must be a Number or a BigNum, not a '%s'\n", CSTRING(IoMessage_name(m)), IoObject_name(other));
	return result;
}
