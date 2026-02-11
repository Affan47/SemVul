FindSymbol(char * name, struct Context * startContext, struct Context * endContext, unsigned int isStruct, unsigned int globalNameSpace)
{
struct Context * ctx;
struct Symbol * symbol = (((void *)0));

for(ctx = startContext; ctx && !symbol; ctx = ctx->parent)
{
if(ctx == globalContext && !globalNameSpace)
{
symbol = (((void *)0));
if(thisNameSpace)
{
char curName[1024];

strcpy(curName, thisNameSpace);
strcat(curName, "::");
strcat(curName, name);
symbol = FindWithNameSpace(isStruct ? &ctx->structSymbols : &ctx->symbols, curName);
}
if(!symbol)
symbol = FindWithNameSpace(isStruct ? &ctx->structSymbols : &ctx->symbols, name);
}
else if(isStruct)
symbol = (struct Symbol *)__ecereMethod___ecereNameSpace__ecere__sys__BinaryTree_FindString(&ctx->structSymbols, name);
else
symbol = (struct Symbol *)__ecereMethod___ecereNameSpace__ecere__sys__BinaryTree_FindString(&ctx->symbols, name);
if(symbol || ctx == endContext)
break;
}
if(inCompiler && curExternal && symbol && ctx == globalContext && curExternal->symbol && symbol->id > curExternal->symbol->idCode && symbol->pointerExternal)
{
if(symbol->pointerExternal->type == 0)
{
struct FunctionDefinition * function = symbol->pointerExternal->function;
struct Context * tmpContext = curContext;

curContext = (((void *)0));
symbol->pointerExternal = MkExternalDeclaration(MkDeclaration(CopyList(function->specifiers, CopySpecifier), MkListOne(MkInitDeclarator(CopyDeclarator(function->declarator), (((void *)0))))));
curContext = tmpContext;
symbol->pointerExternal->symbol = symbol;
DeclareType(symbol->type, 0x1, 0x1);
__ecereMethod___ecereNameSpace__ecere__sys__OldList_Insert((&*ast), curExternal->prev, symbol->pointerExternal);
symbol->id = curExternal->symbol->idCode;
}
else if(symbol->pointerExternal->type == 1 && curExternal->symbol->idCode < symbol->pointerExternal->symbol->id)
{
__ecereMethod___ecereNameSpace__ecere__sys__OldList_Move((&*ast), symbol->pointerExternal, curExternal->prev);
symbol->id = curExternal->symbol->idCode;
}
}
return symbol;
}
