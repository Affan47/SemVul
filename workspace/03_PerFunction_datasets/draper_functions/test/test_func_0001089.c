Find_Include(section **Section, char* String, const char *FileName, int Flags)
{
	char *sPtr;
	section *Ptr = NULL;
	char Help1[SHORT_STRING_SIZE];
	char Help2[SHORT_STRING_SIZE] = "";

	strcpy(Help1,String);
	Kill_Blanks(Help1);

	if (!strncasecmp(S_KEY_INCLUDE,Help1,strlen(S_KEY_INCLUDE)) &&
	    Help1[strlen(S_KEY_INCLUDE)] == C_BEGIN_INCLUDE         &&
	    Help1[strlen(Help1)-1]       == C_END_INCLUDE             )
	{
		Ptr = *Section;

		if (Ptr != NULL)
			while (Ptr->next != NULL)
				Ptr = Ptr->next;

		if (*(Help1+strlen(S_KEY_INCLUDE)+1) != C_SLASH)
		{
			if ((sPtr = strrchr(Help2,C_SLASH)) != NULL)
			{
				strcpy(Help2,FileName);
				sPtr[1] = '\0';
			}
		}

		Help1[strlen(Help1)-1] = '\0';
		strcat(Help2,Help1+strlen(S_KEY_INCLUDE)+1);

		if ((Ptr = read_file(Ptr,Help2,Flags & ~C_NO_WARN_FILE)) == NULL)
			return -1;
		else
			if (*Section == NULL)
				*Section = Ptr;

		return 0;
	}

	return -1;
}
