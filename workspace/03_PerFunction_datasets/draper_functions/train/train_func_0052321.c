jclass_localvariable_attribute_new(const AttributeContainer* container)
{
	LocalVariableAttribute* localvariabletable;
	uint32_t offset;
	uint16_t counter;


	localvariabletable = (LocalVariableAttribute*)
		malloc(sizeof(LocalVariableAttribute));
	localvariabletable->length = UINT16_NATIVE(*((uint16_t*) &container->contents[0]));
	offset = 2;

	if(localvariabletable->length)
		localvariabletable->localvariable = (LocalVariableInfo*)
			malloc(localvariabletable->length * sizeof(LocalVariableInfo));
	else
		localvariabletable->localvariable = NULL;

	for(counter = 0; counter < localvariabletable->length; counter++)
	{
		localvariabletable->localvariable[counter].start_pc = UINT16_NATIVE(*((uint16_t*) &container->contents[offset]));
		offset += 2;

		localvariabletable->localvariable[counter].length = UINT16_NATIVE(*((uint16_t*) &container->contents[offset]));
		offset += 2;

		localvariabletable->localvariable[counter].name_index = UINT16_NATIVE(*((uint16_t*) &container->contents[offset]));
		offset += 2;

		localvariabletable->localvariable[counter].descriptor_index = UINT16_NATIVE(*((uint16_t*) &container->contents[offset]));
		offset += 2;

		localvariabletable->localvariable[counter].index = UINT16_NATIVE(*((uint16_t*) &container->contents[offset]));
		offset += 2;
	}

	return localvariabletable;
}
