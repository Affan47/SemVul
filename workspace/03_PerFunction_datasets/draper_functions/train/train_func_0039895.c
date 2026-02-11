add_buf_list(BUF_NODE * ol , BUF_NODE *ne){
BUF_NODE * bi;
	if (ne == NULL)
		return;
	bi = ol;
	if (bi == NULL){
		printf(" error: the newlist not exist\n");
		exit(0);
	}
	while ( bi->next != NULL)
		bi = bi->next;
	bi->next = ne;
}
