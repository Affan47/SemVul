addEnumValue(const char *typeNameArg, const char *valNameArg,
			  int val)


{
    struct SoEnumEntry	*e = NULL;
    SbName typeName = stripWhite(typeNameArg);
    SbName valName = stripWhite(valNameArg);


    for (int i=0; i<enums.getLength(); i++) {
	e = (struct SoEnumEntry *) enums[i];
	if (e->typeName == typeName)
	    break;
	else
	    e = NULL;
    }

    if (e == NULL) {
	e = new SoEnumEntry(typeName);
	enums.append((void*) e);
    }

    if (e->num == e->arraySize) {
	e->arraySize += SoEnumEntry::growSize;
	int *ovals = e->vals;
	SbName *onames = e->names;
	e->vals = new int[e->arraySize];
	e->names = new SbName[e->arraySize];
	for (int i=0; i<e->num; i++) {
	    e->vals[i] = ovals[i];
	    e->names[i] = onames[i];
	}
	delete [] ovals;
	delete [] onames;
    }
    e->vals[e->num] = val;
    e->names[e->num] = valName;
    e->num++;
}
