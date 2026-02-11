addToCopyDict() const


{

    SoNode *copy = (SoNode *) checkCopy(this);
    if (copy == NULL) {


	copy = (SoNode *) getTypeId().createInstance();
	copy->ref();
	addCopy(this, copy);
	copy->unrefNoDelete();


	SoChildList *kids = getChildren();
	if (kids != NULL)
	    for (int i = 0; i < kids->getLength(); i++)
		(*kids)[i]->addToCopyDict();
    }

    return copy;
}
