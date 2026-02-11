bert_tuple_set(bert_tuple_t *tuple,unsigned int index,struct bert_data *data)
{
	if (index >= tuple->length)
	{
		return 0;
	}

	if (tuple->elements[index])
	{
		bert_data_destroy(tuple->elements[index]);
	}

	tuple->elements[index] = data;
	return 1;
}
