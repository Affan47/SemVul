stack_node_arguments(const ParseNode *node, ArgsData *ad)
{
	iff (node->type == PT_ARRAY, "stack-args: contains value")
	{
		GArray *nodes = (GArray *) node->value;
		const char *id = parse_find_value(nodes, "level");

		nodes = parse_find_array(nodes, "args");

		iff (id && nodes, "no level or args")
		{
			if (ad->valid)
			{
				char *fid;

				gtk_tree_model_get(model, &ad->iter, STACK_ID, &fid, -1);
				ad->valid = !strcmp(id, fid);
				g_free(fid);
			}

			if (!ad->valid)
				ad->valid = model_find(model, &ad->iter, STACK_ID, id);

			iff (ad->valid, "%s: level not found", id)
			{
				StackData sd;

				sd.string = g_string_sized_new(0xFF);
				gtk_tree_model_get(model, &ad->iter, STACK_ENTRY, &sd.entry, -1);
				array_foreach(nodes, (GFunc) append_argument_variable, &sd);
				gtk_list_store_set(store, &ad->iter, STACK_ARGS, sd.string->str, -1);
				g_string_free(sd.string, TRUE);
				ad->valid = ad->sorted && gtk_tree_model_iter_next(model, &ad->iter);
			}
		}
	}
}
