Compiler_Error(char * format, ...)
{
if(inCompiler)
{
if(!parsingType)
{
va_list args;
char string[10000];

if(yylloc.start.included)
{
__ecereFunction___ecereNameSpace__ecere__sys__GetWorkingDir(string, sizeof string);
__ecereFunction___ecereNameSpace__ecere__sys__PathCat(string, GetIncludeFileFromID(yylloc.start.included));
}
else
{
__ecereFunction___ecereNameSpace__ecere__sys__GetWorkingDir(string, sizeof string);
__ecereFunction___ecereNameSpace__ecere__sys__PathCat(string, sourceFile);
}
printf(string);
printf(__ecereNameSpace__ecere__GetTranslatedString(__thisModule, ":%d:%d: error: ", (((void *)0))), yylloc.start.line, yylloc.start.charPos);
__builtin_va_start(args, format);
vsnprintf(string, sizeof string, format, args);
string[sizeof string - 1] = (char)0;
__builtin_va_end(args);
fputs(string, (bsl_stdout()));
((struct __ecereNameSpace__ecere__com__Application *)(((char *)((struct __ecereNameSpace__ecere__com__Module *)(((char *)__thisModule + 24)))->application + 560)))->exitCode = 1;
}
else
{
parseTypeError = 0x1;
}
}
}
