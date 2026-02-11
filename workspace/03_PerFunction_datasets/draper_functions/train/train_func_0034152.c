ProcessFunction(struct FunctionDefinition * function)
{
if(function->body)
{
ProcessStatement(function->body);
if(function->tempCount)
{
struct Statement * stmt = function->body;
int c;

if(!stmt->compound.declarations)
stmt->compound.declarations = MkList();
curContext = stmt->compound.context;
for(c = 1; c <= function->tempCount; c++)
{
char ecereTemp[100];

sprintf(ecereTemp, "__ecereTemp%d", c);
__ecereMethod___ecereNameSpace__ecere__sys__OldList_Insert((&*stmt->compound.declarations), (((void *)0)), QMkDeclarationBase(301, MkInitDeclarator(QMkPtrDecl(ecereTemp), (((void *)0)))));
}
curContext = stmt->compound.context->parent;
}
}
}
