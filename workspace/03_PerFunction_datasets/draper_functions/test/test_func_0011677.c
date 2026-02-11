moveObject(Object *object) {
	if (isInNewSpace(object))
		return;

	int size = object->getHeapSize();
	size_t address = (size_t)allocateInNewSpace(size);

	if (address == (size_t)-1) {
		fprintf(stderr, "error moving object (size %d) with id %d, old space %d, new space %d\n", size, object->getID(), getUsedSpace(false), getUsedSpace(true));
		exit(1);
	}
	memcpy((void *) address, (void *) object->getAddress(), size);

	object->updateAddress((void *) address);
	object->setForwarded(true);
}
