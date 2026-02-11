clone(TStructureMap& remapper)
{
	TFunction *function = new TFunction(*this, remapper);

	return function;
}
