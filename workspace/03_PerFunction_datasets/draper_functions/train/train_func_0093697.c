DebugFindCtxTree(struct __ecereNameSpace__ecere__sys__OldList * ast, int line, int charPos)
{
struct Identifier * idResult;
struct External * external;

__ecereFunction_SetThisClass((((void *)0)));
if(ast != (((void *)0)))
{
for(external = ast->first; external; external = external->next)
{
switch(external->type)
{
case 0:
if(InsideIncl(&external->loc, line, charPos))
{
idResult = DebugFindCtxFunction(external->function, line, charPos);
if(idResult)
return (idResult == (void *)-1 || idResult == (void *)-2) ? (((void *)0)) : idResult;
}
break;
case 1:
if(InsideIncl(&external->loc, line, charPos))
{
idResult = DebugFindCtxDeclaration(external->declaration, line, charPos);
if(idResult)
return (idResult == (void *)-1 || idResult == (void *)-2) ? (((void *)0)) : idResult;
}
break;
case 2:
if(InsideIncl(&external->_class->loc, line, charPos))
{
currentClass = external->_class->symbol->registered;
idResult = DebugFindCtxClass(external->_class, line, charPos);
if(idResult)
return (idResult == (void *)-1 || idResult == (void *)-2) ? (((void *)0)) : idResult;
currentClass = (((void *)0));
}
break;
}
}
}
return (((void *)0));
}
