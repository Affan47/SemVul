copy_str_dynamic(char * originalStr)
{
	if(originalStr == NULL)
		return NULL;


	char * newStrPointer = (char *) malloc((strlen(originalStr) + 1) * sizeof(char));

	if(newStrPointer == NULL)
	{
		printf("error with malloc\n");
		return NULL;
	}

	strcpy(newStrPointer, originalStr);

	return newStrPointer;
}
