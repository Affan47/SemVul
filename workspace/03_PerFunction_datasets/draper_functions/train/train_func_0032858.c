addToRoot(Object* newObject, int thread) {
	if (!doesObjectExistInList(newObject)) {
		add(newObject);
	}
	rootset[thread][newObject->getID()] = newObject;
	rootCount++;

	return 0;
}
