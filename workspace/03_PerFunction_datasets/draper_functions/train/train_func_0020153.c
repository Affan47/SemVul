tomoyo_print_namespace(struct tomoyo_io_buffer *head)
{
	if (!tomoyo_namespace_enabled)
		return;
	tomoyo_set_string(head,
			  container_of(head->r.ns,
				       struct tomoyo_policy_namespace,
				       namespace_list)->name);
	tomoyo_set_space(head);
}
