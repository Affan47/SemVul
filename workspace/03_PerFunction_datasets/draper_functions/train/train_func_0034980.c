fauhdli_kernel_clear_event(struct slset *all_sigs)
{
	struct slset_entry *i;

	for (i = all_sigs->first; i != NULL; i = i->next) {
		signal_clear_event((struct signal *)i->data);
	}
}
