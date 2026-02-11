cm_stop_all(struct cm_context *context)
{
	int i;
	for (i = 0; i < context->n_entries; i++) {
		talloc_free(context->events[i].next_event);
		context->events[i].next_event = NULL;
		cm_iterate_done(context->entries[i],
				context->events[i].iterate_state);
		context->events[i].iterate_state = NULL;
		cm_store_entry_save(context->entries[i]);
	}
	for (i = 0; i < context->n_cas; i++) {
		cm_store_ca_save(context->cas[i]);
	}
}
