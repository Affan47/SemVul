__ecereNameSpace__ecere__sys__SplitArchivePath(char * fileName, char * archiveName, char ** archiveFile)
{
if(fileName[0] == '<')
{
int c = strlen(fileName);

for(; c > 0 && fileName[c] != '>'; c--)
;
if(c > 0)
{
strncpy(archiveName, fileName + 1, c - 1);
archiveName[c - 1] = '\0';
*archiveFile = fileName + c + 1;
return 0x1;
}
}
else if(fileName[0] == ':')
{
strcpy(archiveName, ":");
*archiveFile = fileName + 1;
return 0x1;
}
return 0x0;
}
