is_supported_type_p(const Type *t)
{
    size_t i;

    for (i = 0; i < sizeof(types)/sizeof(types[0]); i++)
	if (t->type == types[i].type)
	    return 1;
    return 0;
}
