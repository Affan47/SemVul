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
__ecereNameSpace__ecere__sys__GetWorkingDir(string, sizeof string);
__ecereNameSpace__ecere__sys__PathCat(string, GetIncludeFileFromID((unsigned int)yylloc.start.included));
}
else
{
__ecereNameSpace__ecere__sys__GetWorkingDir(string, sizeof string);
__ecereNameSpace__ecere__sys__PathCat(string, sourceFile);
}
printf(string);
printf(":%d:%d: error: ", yylloc.start.line, yylloc.start.charPos);
__builtin_va_start(args, format);
vsprintf(string, format, args);
__builtin_va_end(args);
fputs(string, (bsl_stdout()));
((struct __ecereNameSpace__ecere__com__Application *)(((char *)((struct __ecereNameSpace__ecere__com__Module *)(((char *)__thisModule + 12)))->application + 296)))->exitCode = 1;
}
else
{
parseTypeError = 0x1;
}
}
}
