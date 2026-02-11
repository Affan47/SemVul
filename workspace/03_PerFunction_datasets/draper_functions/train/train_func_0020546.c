field_store_ulint(

	Field*	field,
	ulint	n)
{
	int	ret;

	if (n != ULINT_UNDEFINED) {

		ret = field->store(n);
		field->set_notnull();
	} else {

		ret = 0;
		field->set_null();
	}

	return(ret);
}
