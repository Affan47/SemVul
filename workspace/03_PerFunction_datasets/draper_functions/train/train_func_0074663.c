PriorityQueue_create(int (*compareData)(void *, void *))
{
	if(compareData == NULL)
		return NULL;

	AVLTree * tree = AVLTree_create(compareData);

	if(tree == NULL)
		return NULL;

	PriorityQueue * queue = malloc(sizeof(PriorityQueue));
	if(queue == NULL)
		return NULL;

	queue->tree = tree;

	return queue;
}
