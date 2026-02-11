fauhdli_destroy_data_seg(
	struct slist *seg,
	const struct glue_vhdl_cb *callbacks
)
{
	struct slist_entry *i;

	if (seg == NULL) {
		return;
	}

	for (i = seg->first; i != NULL; i = i->next) {
		fauhdli_destroy_data_definition(
			(struct data_definition*)i->data,
			callbacks);
	}

	slist_destroy(seg, callbacks->free);
}
