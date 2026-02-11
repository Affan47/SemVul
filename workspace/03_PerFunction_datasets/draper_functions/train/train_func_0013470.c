o_call(FUNC UNUSED *fp, long index, long argcount)
{
	VALUE result;

	result = builtinfunc(index, (int) argcount, stack);
	while (--argcount >= 0)
		freevalue(stack--);
	stack++;
	*stack = result;
}
