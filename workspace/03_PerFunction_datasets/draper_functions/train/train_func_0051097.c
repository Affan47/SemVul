list_stack_frame (StackTrace *self, guint thread, gboolean update)
{
	GtkTreeModel *model;
	GtkTreeIter iter;
	gboolean found;
	gboolean dirty;

	model = gtk_tree_view_get_model (self->treeview);

	if (!update)
	{

		found = find_thread (model, &iter, thread);
		if (found)
		{

			gtk_tree_model_get(model, &iter, STACK_TRACE_DIRTY_COLUMN, &dirty, -1);
		}
	}


	if (update || !found || dirty)
	{
		StackPacket *packet;

		if (thread != self->current_thread)
		{

			dma_queue_set_thread (self->debugger, thread);
			g_signal_handler_block (self->plugin, self->changed_handler);
		}
		packet = g_slice_new (StackPacket);
		packet->thread = thread;
		packet->self = self;
		packet->scroll = update;
		packet->unblock = thread != self->current_thread;
		dma_queue_list_frame (self->debugger,
							(IAnjutaDebuggerCallback)on_stack_trace_updated,
							packet);
		if (thread != self->current_thread) dma_queue_set_thread (self->debugger, self->current_thread);
	}
}
