on_stack_frames(GArray *nodes)
{
	if (!g_strcmp0(parse_grab_token(nodes), thread_id))
	{
		char *fid = g_strdup(frame_id);

		stack_clear();
		array_foreach(parse_lead_array(nodes), (GFunc) stack_node_location, fid);
		g_free(fid);

		if (!frame_id)
		{
			GtkTreeIter iter;

			if (model_find(model, &iter, STACK_ID, "0"))
				utils_tree_set_cursor(selection, &iter, -1);
		}
	}
}
