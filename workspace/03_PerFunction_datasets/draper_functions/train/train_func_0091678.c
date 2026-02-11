SetResizeParent(bool bRemove, bool bAdd) {
	if(GetParent() == NULL) {
		return;
	}

	my_RemoveResizeParent = bRemove;
	my_AddResizeParent = bAdd;
}
