bert_data_create_false()
{
	bert_data_t *new_data;

	if (!(new_data = bert_data_create()))
	{

		return NULL;
	}

	new_data->type = bert_data_boolean;
	new_data->boolean = 0;
	return new_data;
}
