initAllocators(int heapsize) {
	int i;
	int* genSizes = computeHeapsizes(heapsize);
	for (i = 0; i < GENERATIONS; i++) {
		switch (_allocator) {
			case realAlloc:
				myAllocators[i] = new RealAllocator();
				break;
			case basicAlloc:
				myAllocators[i] = new BasicAllocator();
				break;
			case nextFitAlloc:
				myAllocators[i] = new NextFitAllocator();
				break;

		}
		myAllocators[i]->initializeHeap(genSizes[i]);
	}
}
