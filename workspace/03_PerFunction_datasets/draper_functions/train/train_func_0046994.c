ay_connection_input_remove(int tag)
{
	GSList *input = ay_input_callback_data_list;

	while (input) {
		if (((AyInputCallbackData *)input->data)->tag == tag) {
			eb_input_remove(tag);
			void *tmp = input->data;
			ay_input_callback_data_list =
				g_slist_remove(ay_input_callback_data_list,
				tmp);
			g_free(tmp);

			return;
		}

		input = g_slist_next(input);
	}
}
