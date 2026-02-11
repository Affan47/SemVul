free_undo_block()
{
	config_item_undo *ptr;

	ptr = Config_item_undo;
	if (!ptr) {
		return;
	}

	Config_item_undo = ptr->next;
	if (ptr->size) {
		vm_free(ptr->list);
		vm_free(ptr->index);
	}

	vm_free(ptr);
}
