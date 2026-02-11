lookup_tuple_method(cell obj, cell methods)
{
	tuple_layout *layout = untag<tuple_layout>(untag<tuple>(obj)->layout);

	array *echelons = untag<array>(methods);

	fixnum echelon = std::min(untag_fixnum(layout->echelon),(fixnum)array_capacity(echelons) - 1);

	while(echelon >= 0)
	{
		cell echelon_methods = array_nth(echelons,echelon);

		if(tagged<object>(echelon_methods).type_p(WORD_TYPE))
			return echelon_methods;
		else if(to_boolean(echelon_methods))
		{
			cell klass = nth_superclass(layout,echelon);
			cell hashcode = untag_fixnum(nth_hashcode(layout,echelon));
			cell result = search_lookup_hash(echelon_methods,klass,hashcode);
			if(to_boolean(result))
				return result;
		}

		echelon--;
	}

	critical_error("Cannot find tuple method",methods);
	return false_object;
}
