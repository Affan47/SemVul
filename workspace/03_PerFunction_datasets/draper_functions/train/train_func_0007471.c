free_tableswitch_list(struct compilation_unit *cu)
{
	struct tableswitch *this, *next;

	list_for_each_entry_safe(this, next, &cu->tableswitch_list, list_node) {
		list_del(&this->list_node);
		free_tableswitch(this);
	}
}
