printNames() {
	GLEStringHash* children = getChilds();
	if (children != NULL) {
		GLEStringHashData* hash = children->getHash();
		for (GLEStringHashData::const_iterator i = hash->begin(); i != hash->end(); i++) {
			GLEString* child_name = i->first.get();
			GLEObjectRepresention* child = (GLEObjectRepresention*)children->getObject(i->second);
			cout << *child_name << ": " << *child->getRectangle() << endl;
			child->printNames();
		}
	}
}
