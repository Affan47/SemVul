swap() {


	int i;
	Object *currentObj;

	vector<Object*> objects = myObjectContainer->getLiveObjects();
	for (i = 0; i < (int)objects.size(); i++) {
		currentObj = objects[i];
		if (currentObj) {
			if (!myAllocator->isInNewSpace(currentObj)) {
				if (!currentObj->isForwarded()) {
					statFreedObjects++;
					statFreedDuringThisGC++;
				}
				myMemManager->requestDelete(currentObj, myGeneration == GENERATIONS - 1 ? 1 : 0);

			}
		}
	}


	myAllocator->freeOldSpace();

	myAllocator->swapHeaps();
}
