IsFlag(char *Flag, int FlagIndex)
{
	char *RetCode = NULL;
	int Len = strlen(ValidFlags[FlagIndex].name);

	if ((RetCode = strstr(Flag,ValidFlags[FlagIndex].name)) != NULL     &&
			Flag == RetCode                                                   )
	{
		if (ValidFlags[FlagIndex].number == 0)
		{
			if (Flag[Len] == '\0')
				return RetCode;
		}
		else
		{
		  if (*(RetCode = &(Flag[Len])) == C_DELIMITER_FLAG_AND_OPT )
				return (RetCode+1);
			else
			{
				print_msg(PRT_ERR,"Warning: invalid option string \"%s\"!\n",Flag);
				return NULL;
			}
		}
	}

	return NULL;
}
