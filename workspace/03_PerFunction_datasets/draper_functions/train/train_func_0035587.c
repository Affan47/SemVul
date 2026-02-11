Log_ (ConfigS *configSP, RuntimeS *runtimeSP)
{
char		*remainderP;
char		tokenA[STRINGSIZE];
char		token_copyA[STRINGSIZE];
char		*P;
int		n;
static char	*env_valueP;
char		path_nameA[STRINGSIZE];


remainderP = ExtractToken_ (tokenA, STRINGSIZE,
			    runtimeSP->curr_commandA, " \t\n");
if (!remainderP) return ERROR_LOG;


remainderP = ExtractToken_ (tokenA, STRINGSIZE, remainderP, " \t\n");
if (!remainderP)
	{
	strcpy (runtimeSP->messageA, "Log file not specified!");
	runtimeSP->message_length = strlen (runtimeSP->messageA);
	return ERROR_NO_FILE_NAME;
	}


strncpy (token_copyA, tokenA, STRINGSIZE - 1);
token_copyA[STRINGSIZE - 1] = '\0';
P = token_copyA;
while ((n = *P++) != '\0') *(P - 1) = toupper (n);
if (strstr (token_copyA, "OFF") == token_copyA)
	{
	fclose (configSP->log_fileP);
	configSP->log_fileF = 0;
	configSP->log_fileP = NULL;
	configSP->log_file_nameA[0] = '\0';
	return COMMAND_LOG;
	}


if (configSP->log_fileF)
	{
	fclose (configSP->log_fileP);
	configSP->log_fileF = 0;
	configSP->log_fileP = NULL;
	configSP->log_file_nameA[0] = '\0';
	}


configSP->log_fileP = fopen (tokenA, "w");


if (configSP->log_fileP == NULL)
	{

	P = tokenA;
	if (*P == '/') P++;


	if ((env_valueP = getenv ("HOME")) != NULL)
		{

		strncpy (path_nameA, env_valueP, STRINGSIZE - 1);
		path_nameA[STRINGSIZE - 1] = '\0';


		n = (int) strlen (path_nameA) - 1;
		if (path_nameA[n] != '/') strcat (path_nameA, "/");


		n = STRINGSIZE - (int) strlen (path_nameA) - 1;
		strncat (path_nameA, P, n);
		path_nameA[STRINGSIZE - 1] = '\0';


		configSP->log_fileP = fopen (path_nameA, "w");
		}
	}

if (configSP->log_fileP == NULL)
	{
	sprintf (runtimeSP->messageA, "Unable to open log file %s!", tokenA);
	runtimeSP->message_length = strlen (runtimeSP->messageA);
	return ERROR_OPEN_FAILURE;
	}


strncpy (configSP->log_file_nameA, tokenA, STRINGSIZE - 1);
configSP->log_file_nameA[STRINGSIZE - 1] = '\0';
configSP->log_fileF = 1;


return COMMAND_LOG;
}
