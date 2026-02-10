merge (Node *nodeA, Node *nodeB, int (*cmp) (Node *a, Node *b))
{
	Node *thead, *tnode;

	if (!nodeA)
		return nodeB;
	if (!nodeB)
		return nodeA;


	if (cmp (nodeA, nodeB) <= 0) {
		thead = nodeA;
		nodeA = nodeA->down;
		thead->down = NULL;
	} else {
		thead = nodeB;
		nodeB = nodeB->down;
		thead->down = NULL;
	}

	tnode = thead;


	while (nodeA && nodeB) {
		if (cmp (nodeA, nodeB) <= 0) {
			tnode->down = nodeA;
			nodeA->up = tnode;
			tnode = nodeA;
			nodeA = nodeA->down;
		} else {
			tnode->down = nodeB;
			nodeB->up = tnode;
			tnode = nodeB;
			nodeB = nodeB->down;
		}
	}


	if (nodeA) {
		tnode->down = nodeA;
		nodeA->up = tnode;
	} else if (nodeB) {
		tnode->down = nodeB;
		nodeB->up = tnode;
	} else {
		tnode->down = NULL;
	}

	return thead;
}
