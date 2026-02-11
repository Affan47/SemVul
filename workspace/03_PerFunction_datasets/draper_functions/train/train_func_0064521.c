__ecereNameSpace__ecere__sys__FileExists(char * fileName)
{
char archiveName[797], * archiveFile;

if(__ecereNameSpace__ecere__sys__SplitArchivePath(fileName, archiveName, &archiveFile))
{
return ((unsigned int (*)(char *  archive, char *  fileName))__ecereClass___ecereNameSpace__ecere__sys__EARFileSystem->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__sys__FileSystem_Exists])(archiveName, archiveFile);
}
else if(strstr(fileName, "http://") == fileName)
{
return (((unsigned int)(0x1)));
}
else
return FILE_FileExists(fileName);
}
