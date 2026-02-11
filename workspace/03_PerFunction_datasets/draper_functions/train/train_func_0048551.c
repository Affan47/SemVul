bert_data_create_float(double f)
{
	bert_data_t *new_data;

	if (!(new_data = bert_data_create()))
	{

		return NULL;
	}

	new_data->type = bert_data_float;
	new_data->floating_point = f;
	return new_data;
}
