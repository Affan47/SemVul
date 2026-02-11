jit_stack_frame_p(F_ARRAY *array)
{
	F_FIXNUM length = array_capacity(array);
	F_FIXNUM i;

	for(i = 0; i < length - 1; i++)
	{
		if(type_of(array_nth(array,i)) == WORD_TYPE)
			return true;
	}

	return false;
}
