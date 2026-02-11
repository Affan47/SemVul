GetIncludeFileID(char * includeFile)
{
int found = FindIncludeFileID(includeFile);

if(found)
return found;
includes = __ecereNameSpace__ecere__com__eSystem_Renew(includes, sizeof(char *) * (numIncludes + 1));
includes[numIncludes++] = __ecereNameSpace__ecere__sys__CopyString(includeFile);
return numIncludes;
}
