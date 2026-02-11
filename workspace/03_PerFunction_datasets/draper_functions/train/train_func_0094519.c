MkDeclarationInst(struct Instantiation * inst)
{
struct Declaration * decl = (decl = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass_Declaration), decl->type = 2, decl->inst = inst, decl->loc = yylloc, decl);
struct Symbol * symbol;

if(curContext == globalContext && (currentNameSpace || defaultNameSpace) && declMode != 0 && defaultDeclMode != 0)
{
char name[1024];
int len = 0, stringLen;

if(defaultNameSpace)
{
memcpy(name, defaultNameSpace, defaultNameSpaceLen);
len += defaultNameSpaceLen;
name[len++] = ':';
name[len++] = ':';
}
if(currentNameSpace)
{
memcpy(name + len, currentNameSpace, currentNameSpaceLen);
len += currentNameSpaceLen;
name[len++] = ':';
name[len++] = ':';
}
stringLen = strlen(inst->exp->identifier->string);
memcpy(name + len, inst->exp->identifier->string, stringLen);
len += stringLen;
name[len] = (char)0;
(__ecereNameSpace__ecere__com__eSystem_Delete(inst->exp->identifier->string), inst->exp->identifier->string = 0);
inst->exp->identifier->string = __ecereNameSpace__ecere__sys__CopyString(name);
}
symbol = __extension__ ({
struct Symbol * __ecereInstance1 = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass_Symbol);

__ecereInstance1->string = (inst->exp->type == 0) ? __ecereNameSpace__ecere__sys__CopyString(inst->exp->identifier->string) : (((void *)0)), __ecereInstance1->type = MkClassTypeSymbol(inst->_class->symbol), __ecereInstance1;
});
symbol->idCode = symbol->id = curContext->nextID++;
if(strstr(symbol->string, "::"))
curContext->hasNameSpace = 0x1;
if(!__ecereMethod___ecereNameSpace__ecere__sys__BinaryTree_Add(&(curContext->templateTypesOnly ? curContext->parent : curContext)->symbols, (struct __ecereNameSpace__ecere__sys__BTNode *)symbol))
__ecereMethod___ecereNameSpace__ecere__sys__OldList_Add((&*excludedSymbols), symbol);
decl->symbol = inst->symbol = symbol;
return decl;
}
