AddStructDefinitions(struct Specifier * spec, struct __ecereNameSpace__ecere__sys__OldList * definitions)
{
spec->definitions = definitions;
if(definitions && spec->id && !declMode)
{
struct Symbol * symbol;
struct __ecereNameSpace__ecere__sys__OldList specs =
{
0, 0, 0, 0, 0
};

__ecereMethod___ecereNameSpace__ecere__sys__OldList_Add(&specs, spec);
symbol = __extension__ ({
struct Symbol * __ecereInstance1 = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass_Symbol);

__ecereInstance1->string = __ecereFunction___ecereNameSpace__ecere__sys__CopyString(spec->id->string), __ecereInstance1->type = ProcessType(&specs, (((void *)0))), __ecereInstance1->isStruct = 0x1, __ecereInstance1;
});
if(!__ecereMethod___ecereNameSpace__ecere__sys__BinaryTree_Add(&curContext->parent->structSymbols, (struct __ecereNameSpace__ecere__sys__BTNode *)symbol))
FreeSymbol(symbol);
}
}
