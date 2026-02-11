gist_box_same(PG_FUNCTION_ARGS)
{
	BOX		   *b1 = PG_GETARG_BOX_P(0);
	BOX		   *b2 = PG_GETARG_BOX_P(1);
	bool	   *result = (bool *) PG_GETARG_POINTER(2);

	if (b1 && b2)
		*result = (b1->low.x == b2->low.x && b1->low.y == b2->low.y &&
				   b1->high.x == b2->high.x && b1->high.y == b2->high.y);
	else
		*result = (b1 == NULL && b2 == NULL);
	PG_RETURN_POINTER(result);
}
