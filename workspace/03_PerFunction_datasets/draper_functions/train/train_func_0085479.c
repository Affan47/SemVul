FreeContext(struct Context * context)
{
struct Symbol * symbol;

while(symbol = (struct Symbol *)context->types.root)
{
__ecereMethod___ecereNameSpace__ecere__sys__BinaryTree_Remove(&context->types, (struct __ecereNameSpace__ecere__sys__BTNode *)symbol);
FreeSymbol(symbol);
}
while(symbol = (struct Symbol *)context->classes.root)
{
__ecereMethod___ecereNameSpace__ecere__sys__BinaryTree_Remove(&context->classes, (struct __ecereNameSpace__ecere__sys__BTNode *)symbol);
FreeSymbol(symbol);
}
while(symbol = (struct Symbol *)context->symbols.root)
{
__ecereMethod___ecereNameSpace__ecere__sys__BinaryTree_Remove(&context->symbols, (struct __ecereNameSpace__ecere__sys__BTNode *)symbol);
FreeSymbol(symbol);
}
while(symbol = (struct Symbol *)context->structSymbols.root)
{
__ecereMethod___ecereNameSpace__ecere__sys__BinaryTree_Remove(&context->structSymbols, (struct __ecereNameSpace__ecere__sys__BTNode *)symbol);
FreeSymbol(symbol);
}
while(symbol = (struct Symbol *)context->templateTypes.root)
{
__ecereMethod___ecereNameSpace__ecere__sys__BinaryTree_Remove(&context->templateTypes, (struct __ecereNameSpace__ecere__sys__BTNode *)symbol);
FreeTemplateType((struct TemplatedType *)symbol);
}
context->nextID = 0;
context->simpleID = 0;
context->parent = (((void *)0));
}
