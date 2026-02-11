insertAtIndex(int index, int newData)
{
	if(index + 1 > length)
	{
		std::cout << "Index too large." << std::endl;
		return;
	}
	if(head == NULL)
	{
		Node *newNode = new Node(newData);
		newNode->setLink(NULL);
		head = newNode;
		length++;
		return;
	}

	Node *temp = head;
	Node *prev = NULL;
	int i = 0;
	while(temp != NULL)
	{
		if(i == index)
		{
			Node *newNode = new Node(newData);
			newNode->setLink(temp);
			prev->setLink(newNode);
			length++;
			return;
		}
		i++;
		prev = temp;
		temp = temp->getLink();
	}
}
