_equalResTarget(ResTarget *a, ResTarget *b)
{
	COMPARE_STRING_FIELD(name);
	COMPARE_NODE_FIELD(indirection);
	COMPARE_NODE_FIELD(val);
	COMPARE_SCALAR_FIELD(location);

	return true;
}
