PositiveMultiply(Integer &product, const Integer &a, const Integer &b)
{
	size_t aSize = RoundupSize(a.WordCount());
	size_t bSize = RoundupSize(b.WordCount());

	product.reg.CleanNew(RoundupSize(aSize+bSize));
	product.sign = Integer::POSITIVE;

	IntegerSecBlock workspace(aSize + bSize);
	AsymmetricMultiply(product.reg, workspace, a.reg, aSize, b.reg, bSize);
}
