nd_prepend(Node *nd, Node *new_head){
	Node *old_head = nd->head;

	nd->head = new_head;

	new_head->tail = nd;
	new_head->head = old_head;

	if(old_head){
		old_head->tail = new_head;
	}
	return new_head;
}
