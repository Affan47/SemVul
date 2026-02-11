NotBalanceInsert(WordNode *node, char *s){
	if (!insertStr)
		insertStr = s;
	if (node == 0)
	{
		node = (WordNode*) malloc(sizeof(WordNode));
		if (node==NULL)
			return NULL;
		node->split_char = *s;
		node->lchild = node->mchild = node->rchild = NULL;
		node->key = NULL;
		node->parent = currParent;
		node->h = 0;
	}
	if (*s < node->split_char)
	{
		currParent = node;
		node->h++;
		node->lchild = NotBalanceInsert(node->lchild, s);
	} else if (*s > node->split_char)
	{
		currParent = node;
		node->h++;
		node->rchild = NotBalanceInsert(node->rchild, s);
	} else {
		if (*(s+1) == '\0'){
			char *temp = (char*) malloc((strlen(insertStr)+1)*sizeof(char));
			if (temp==NULL)
				return node;
			node->key = strcpy(temp, insertStr);
		}
		else
		{
			currParent = node;
			node->mchild = NotBalanceInsert(node->mchild, ++s);
		}
	}
	if (insertStr)
		insertStr = 0;
	return node;
}
