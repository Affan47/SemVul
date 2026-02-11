discrete_stream_update_mono(int ch,INT16 *buffer, int length)
{

	int loop,loop2,loop3;
	struct node_description *node;

	for(loop=0;loop<length;loop++)
	{
		for(loop2=0;loop2<node_count;loop2++)
		{

			node=running_order[loop2];


			for(loop3=0;loop3<node->active_inputs;loop3++)
			{
				if(node->input_node[loop3] && (node->input_node[loop3])->node!=NODE_NC) node->input[loop3]=(node->input_node[loop3])->output;
			}


			if(module_list[node->module].step) (*module_list[node->module].step)(node);
		}


		buffer[loop]=(((struct dso_output_context*)(output_node->context))->left+((struct dso_output_context*)(output_node->context))->right)/2;
	}
#ifdef DISCRETE_WAVELOG
	wav_add_data_16(wav_file, buffer, length);
#endif
}
