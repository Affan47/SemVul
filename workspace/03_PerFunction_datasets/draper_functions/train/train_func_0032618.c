attr_syntax_enumerate_attrs_ext( PLHashTable *ht,
                                 AttrEnumFunc aef, void *arg )
{
	struct enum_arg_wrapper eaw;
	eaw.aef = aef;
	eaw.arg = arg;

	if (!ht)
		return;

	PL_HashTableEnumerateEntries(ht, attr_syntax_enumerate_internal, &eaw);
}
