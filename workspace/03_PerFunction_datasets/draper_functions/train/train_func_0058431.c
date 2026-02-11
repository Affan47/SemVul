geqo_selection(Chromosome *momma, Chromosome *daddy, Pool *pool, double bias)
{
	int			first,
				second;

	first = linear(pool->size, bias);
	second = linear(pool->size, bias);

	if (pool->size > 1)
	{
		while (first == second)
			second = linear(pool->size, bias);
	}

	geqo_copy(momma, &pool->data[first], pool->string_length);
	geqo_copy(daddy, &pool->data[second], pool->string_length);
}
