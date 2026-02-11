SaveSecondaryStructure_ (RuntimeS *runtimeSP)
{
char		lineA[STRINGSIZE];
char		*remainderP;
char		tokenA[STRINGSIZE];
FILE		*fileP;
int		codeI;
int		code;


strncpy (lineA, runtimeSP->curr_commandA, STRINGSIZE - 1);
lineA[STRINGSIZE - 1] = '\0';


remainderP = ExtractToken_ (tokenA, STRINGSIZE, lineA, " \t\n");
if (!remainderP) return -1;
remainderP = ExtractToken_ (tokenA, STRINGSIZE, remainderP, " \t\n");
if (!remainderP) return -2;


remainderP = ExtractToken_ (tokenA, STRINGSIZE, remainderP, " \t\n");
if (!remainderP)
	{
	strcpy (runtimeSP->messageA, "File name missing!");
	runtimeSP->message_length = strlen (runtimeSP->messageA);
	return -3;
	}


fileP = fopen (tokenA, "w");
if (fileP == NULL)
	{
	strcpy (runtimeSP->messageA, "Failed to open file!");
	runtimeSP->message_length = strlen (runtimeSP->messageA);
	return -4;
	}


fprintf (fileP, ">1xxx     %d codes\n", runtimeSP->sec_structure_length);


for (codeI = 0; codeI < (int) runtimeSP->sec_structure_length; codeI++)
	{

	code = *(runtimeSP->sec_structureP + codeI);


	fprintf (fileP, "%c", code);


	if (((codeI + 1) % 75) == 0) fprintf (fileP, "\n");
	}


fprintf (fileP, "\n");


fclose (fileP);


return 1;
}
