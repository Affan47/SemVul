MemoryContextCreate(NodeTag tag, Size size,
					MemoryContextMethods *methods,
					MemoryContext parent,
					const char *name)
{
	MemoryContext node;
	Size		needed = size + strlen(name) + 1;


	if (TopMemoryContext != NULL)
	{

		node = (MemoryContext) MemoryContextAlloc(TopMemoryContext,
												  needed);
	}
	else
	{

		node = (MemoryContext) malloc(needed);
		Assert(node != NULL);
	}


	MemSet(node, 0, size);
	node->type = tag;
	node->methods = methods;
	node->parent = NULL;
	node->firstchild = NULL;
	node->nextchild = NULL;
	node->name = ((char *) node) + size;
	strcpy(node->name, name);


	(*node->methods->init) (node);


	if (parent)
	{
		node->parent = parent;
		node->nextchild = parent->firstchild;
		parent->firstchild = node;
	}


	return node;
}
