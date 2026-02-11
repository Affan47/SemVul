delete_parent(struct fib_node* children){
	struct fib_node* c = children;

	if(!c){
		return;
	}

	do{
		c->parent = NULL;
		c = c->next;

	}while( c != children );
}
