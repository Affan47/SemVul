requestFree(Object* object) {


	if (object) {
		int gen = object->getGeneration();
		myAllocators[gen]->gcFree(object);
	}
}
