initGarbageCollectors(int highWatermark) {
	int i;
	for (i = 0; i < GENERATIONS; i++) {
		switch (_collector) {
			case markSweepGC:
				myGarbageCollectors[i] = new MarkSweepCollector();
				break;
			case traversalGC:
				myGarbageCollectors[i] = new TraversalCollector();
				break;
			case markSweepRB:
			    myGarbageCollectors[i] = new RegionBasedMarkSweepCollector();
			    break;
		}
		myGarbageCollectors[i]->setEnvironment(myAllocators[i],	myObjectContainers[i], (MemoryManager*) this, highWatermark, i, _traversal);
		myGarbageCollectors[i]->initializeHeap();
	}
}
