cave_valid_bold(int y, int x)
{
	object_type *o_ptr;


	if (cave_perma_bold(y, x)) return (FALSE);


	for (o_ptr = get_first_object(y, x); o_ptr; o_ptr = get_next_object(o_ptr))
	{

		if (artifact_p(o_ptr)) return (FALSE);
	}


	return (TRUE);
}
