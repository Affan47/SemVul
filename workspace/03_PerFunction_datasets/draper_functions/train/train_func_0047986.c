String_For_Output(char* String)
{
	char *Ptr;
	char *CurPtr;
	char  NewString[LONG_STRING_SIZE];

	strcpy(NewString,String);
	CurPtr = NewString;
	String[0] = '\0';

	while ((Ptr = strtok(CurPtr,"\n\r")) != NULL)
	{
		CurPtr = NULL;
		strcat(String,Ptr);
	}

	return 0;
}
