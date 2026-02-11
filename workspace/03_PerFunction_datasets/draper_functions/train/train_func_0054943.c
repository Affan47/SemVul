test_two()
{
	bert_list_node_t *node = list->head->next;

	if (!node)
	{
		test_fail("bert_list_append should create the second node");
	}

	bert_data_t *data;

	if (!(data = node->data))
	{
		test_fail("bert_list_append should set the second data");
	}

	if (data->type != bert_data_int)
	{
		test_fail("bert_list_append appended the wrong second data");
	}

	if (data->integer != EXPECTED_TWO)
	{
		test_fail("first element is %d, expected %d",data->integer,EXPECTED_TWO);
	}
}
