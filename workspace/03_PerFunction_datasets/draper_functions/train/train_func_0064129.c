constant_pool_add_Integer(struct ClassFile *cf, u4 i)
{
	struct ConstantPool **p = &cf->constant_pool;
	int index = 1;

	while (*p != NULL)
	{
		if ((*p)->tag == CONSTANT_Integer && (*p)->data.i == i)
			return index;
		p = &(*p)->next;
		index++;
	}

	*p = (struct ConstantPool*)malloc(sizeof(struct ConstantPool));

	if (*p)
	{
		(*p)->tag = CONSTANT_Integer;
		(*p)->data.i = i;
		(*p)->next = NULL;
	}

	return ++cf->constant_pool_count;
}
