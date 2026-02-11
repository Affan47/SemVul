IoBigNum_cmp(IoBigNum * self, IoObject * other)
{
	if (ISNUMBER(other))
		return mpz_cmp_si(DATA(self)->integer, IoNumber_asLong(other));
	else if (ISBIGNUM(other))
		return mpz_cmp(DATA(self)->integer, DATA(other)->integer);
	else
		return IoObject_defaultCompare(self, other);
}
