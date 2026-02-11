is_name(GLEObjectRepresention* obj, GLEArrayImpl* path, unsigned int offs) {

	unsigned int size = path->size();
	if (size <= offs) {
		return true;
	}

	for (unsigned int i = offs; i < size; i++) {
		GLEString* elem = (GLEString*)path->getObjectUnsafe(i);
		GLEObjectRepresention* nextobj = obj->getChildObject(elem);
		if (nextobj != NULL) {
			obj = nextobj;
		} else {
			return false;
		}
	}
	return true;
}
