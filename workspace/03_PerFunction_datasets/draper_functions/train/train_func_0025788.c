clear_mixmonitor_recipient_list(struct mixmonitor *mixmonitor)
{
	struct vm_recipient *current;
	while ((current = AST_LIST_REMOVE_HEAD(&mixmonitor->recipient_list, list))) {

		ast_free(current);
	}
}
