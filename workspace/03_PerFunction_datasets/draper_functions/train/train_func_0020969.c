apply_sync_data_to_functions(model_data * modeldata)
{
	xmachine_message * current_message;
	sync * current_sync;
	function_pointer * current_function_pointer;
	xmachine_function * current_function;


	current_message = * modeldata->p_xmessages;
	while(current_message)
	{
		current_sync = current_message->syncs;
		while(current_sync)
		{

			current_function_pointer = current_sync->lastdepend;
			while(current_function_pointer)
			{
				current_function = current_function_pointer->function;


				add_sync_pointer(&current_function->start_syncs, current_sync);


				current_function_pointer = current_function_pointer->next;
			}


			current_function_pointer = current_sync->firstdependent;
			while(current_function_pointer)
			{
				current_function = current_function_pointer->function;


				add_sync_pointer(&current_function->complete_syncs, current_sync);


				current_function_pointer = current_function_pointer->next;
			}

			current_sync = current_sync->next;
		}

		current_message = current_message->next;
	}
}
