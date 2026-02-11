get_element(unsigned int index) {
	const char* routine = "XmlElement::get_element";
	if (index < elements->size())
		return elements->at(index);
	stringstream S;
	S << "Element " << index << " out of range in " << name;
	L_ERROR(LOG_XML,S.str());
	return NULL;
}
