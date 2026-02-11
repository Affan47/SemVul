Times(const PolynomialMod2 &b) const
{
	PolynomialMod2 result((word)0, BitCount() + b.BitCount());

	for (int i=b.Degree(); i>=0; i--)
	{
		result <<= 1;
		if (b[i])
			XorWords(result.reg, reg, reg.size());
	}
	return result;
}
