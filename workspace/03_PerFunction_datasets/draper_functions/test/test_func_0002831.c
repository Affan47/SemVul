SaveSequence_ (RuntimeS *runtimeSP)
{
int		max_length;
char		lineA[STRINGSIZE];
char		*remainderP;
char		tokenA[STRINGSIZE];
FILE		*fileP;
size_t		residueI;
char		*nameP;
char		residue_nameA[RESNAMESIZE];


max_length = RESNAMESIZE - 1;


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


for (residueI = 0; residueI < runtimeSP->residuesN; residueI++)
	{

	nameP = runtimeSP->sequenceP + residueI * max_length;


	strncpy (residue_nameA, nameP, max_length);
	residue_nameA[max_length] = '\0';


	fprintf (fileP, "%-4s", residue_nameA);


	if (((residueI + 1) % 10) == 0) fprintf (fileP, "\n");
	}


fprintf (fileP, "\n");


fclose (fileP);


return 1;
}
