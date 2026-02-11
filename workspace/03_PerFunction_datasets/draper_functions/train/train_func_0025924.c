deque_release(deque_t *deque)
{
	if(!deque){
		return;
	}
	if(deque->release_function){
		size_t counter = 0;
		while(counter != deque->size){
			deque->release_function(refer_by_offset_from_front(deque,counter));
			counter++;
		}
	}
	free(deque->array);
	free(deque);
}
