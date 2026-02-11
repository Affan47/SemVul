deque_PCB_from_blocked_on_receiveQ(PCB *to_deque)
{
	PCB* to_return;
	PCB* prev;

	if(ptr_blocked_on_receiveQ == NULL)
		return NULL;

	else{
		prev = ptr_blocked_on_receiveQ->head;

		if(prev == to_deque){
			ptr_blocked_on_receiveQ->head = ptr_blocked_on_receiveQ->head->next;
			prev->next = NULL;
			return prev;
		}

		for (to_return = ptr_blocked_on_receiveQ->head->next;  to_return != to_deque;
			to_return = to_return->next)
			{prev = prev->next;}

		if(to_return != to_deque)
			return NULL;

		else{
			if(prev->next != NULL)
				prev->next = prev->next->next;
			return to_return;
			to_return->next = NULL;
		}
	}


}
