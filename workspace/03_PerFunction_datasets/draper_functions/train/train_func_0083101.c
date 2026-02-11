longestCollatz(unsigned top){

	uint64_t maxSize = 0;
	uint64_t head = top;
	unsigned maxHead = 0;

	while(head){
		uint64_t count = collatzLen(head);

		if(maxSize < count){
			maxSize = count;
			maxHead = head;
		}

		head -=1;
	}

	return maxHead;
}
