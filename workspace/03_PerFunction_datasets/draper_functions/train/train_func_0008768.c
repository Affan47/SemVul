nd_reverse(Node *nd){
	Node *first = nd;
	Node *end = nd_last(nd);
	Node *next;
	do{
		next = first->tail;

		first->tail->head = NULL;
		first->tail = NULL;

		nd_append(end, first);
		first = next;
	} while(first != end);
	return first;
}
