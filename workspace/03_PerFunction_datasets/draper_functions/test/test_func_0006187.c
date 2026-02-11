AVLPrint(struct tree_node *now, int level) {
	int i=0;
    if(now == AVL_TREE)    return;

	for (i=0; i<level; i++)
		printf("|");

	if (now->expdate[0] > 9)
		printf("%d/", now->expdate[0]);
	else
		printf("0%d/", now->expdate[0]);

	if (now->expdate[1] > 9)
		printf("%d/", now->expdate[1]);
	else
		printf("0%d/", now->expdate[1]);

	printf("%d\n", now->expdate[2]);

    if(now->leftChild != AVL_TREE)    AVLPrint(now->leftChild, level+1);
    if(now->rightChild != AVL_TREE)    AVLPrint(now->rightChild, level+1);
}
