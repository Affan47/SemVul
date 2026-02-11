set(const char *fieldDataString, SoInput *dictIn)


{
    const SoFieldData	*fieldData = getFieldData();

    if (fieldData != NULL) {
	SoInput	in(dictIn);
	in.setBuffer((void *) fieldDataString, strlen(fieldDataString));
	SbBool isBuiltIn;
	return fieldData->read(&in, this, FALSE, isBuiltIn);
    }
    else
	return FALSE;
}
