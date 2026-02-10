cell(idx_type)
{
	static MathData dummyCell(&buffer());
	LYXERR0("I don't have any cell");
	return dummyCell;
}
