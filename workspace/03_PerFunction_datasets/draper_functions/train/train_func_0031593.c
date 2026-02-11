FreeASTTree(struct __ecereNameSpace__ecere__sys__OldList * ast)
{
if(ast != (((void *)0)))
{
struct External * external;

while(external = ast->first)
{
__ecereMethod___ecereNameSpace__ecere__sys__OldList_Remove(ast, external);
FreeExternal(external);
}
(__ecereNameSpace__ecere__com__eSystem_Delete(ast), ast = 0);
}
}
