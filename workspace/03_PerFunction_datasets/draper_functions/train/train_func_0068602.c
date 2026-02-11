FindParamsClassFunction(struct ClassFunction * func, int line, int charPos)
{
if(func->body && Inside(&func->body->loc, line, charPos))
{
struct Identifier * idResult;
struct Identifier * id = __ecereFunction_GetDeclId(func->declarator);
struct Symbol * symbol = func->declarator ? func->declarator->symbol : (((void *)0));
struct Type * type = symbol ? symbol->type : (((void *)0));
struct __ecereNameSpace__ecere__com__Class * oldThisClass = __ecereFunction_GetThisClass();
struct Context * oldTopContext = __ecereFunction_GetTopContext();

__ecereFunction_SetThisClass((type && type->thisClass) ? type->thisClass->registered : currentClass);
idResult = FindParamsStatement(func->body, line, charPos);
if(idResult)
return idResult;
__ecereFunction_SetThisClass(oldThisClass);
__ecereFunction_SetTopContext(oldTopContext);
}
return (((void *)0));
}
