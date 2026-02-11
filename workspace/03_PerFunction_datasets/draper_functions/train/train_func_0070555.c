remove(void *data)
{


	Element *temp = find(data);


	if(temp == NULL)
	{
		cerr << "_LinkedList::remove : element not found" << endl;
		return;

	} else {

			if(temp==head) head = temp->next;
			else temp->prev->next = temp->next;

			if(temp==tail) tail = temp->prev;
			else temp->next->prev = temp->prev;

			delete temp;


			elements--;

			temp = NULL;
	}
}
