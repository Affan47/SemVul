DecAdd(MonoDecimal *value, MonoDecimal* d)
{
	g_assert(value != NULL && d != NULL);

	if (D32AddCarry(&DECIMAL_LO32(*value), DECIMAL_LO32(*d))) {
		if (D32AddCarry(&DECIMAL_MID32(*value), 1)) {
			D32AddCarry(&DECIMAL_HI32(*value), 1);
		}
	}
	if (D32AddCarry(&DECIMAL_MID32(*value), DECIMAL_MID32(*d))) {
		D32AddCarry(&DECIMAL_HI32(*value), 1);
	}
	D32AddCarry(&DECIMAL_HI32(*value), DECIMAL_HI32(*d));
}
