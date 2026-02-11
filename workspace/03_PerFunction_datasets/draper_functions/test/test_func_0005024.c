delete_timer_heap(int idx)
{
	int pos = search_timer_heap(idx);

	if(pos != -1) {
		memmove(&timer_heap[pos],&timer_heap[pos+1],(timer_heap[0] - pos) * sizeof(int));
		timer_heap[0]--;
	}
}
