ProcessInstanceDeclarations()
{
struct External * external;

curContext = globalContext;
for(external = (*ast).first; external; external = external->next)
{
curExternal = external;
if(external->type == 0)
{
struct FunctionDefinition * func = external->function;

if(func->specifiers)
{
struct Specifier * spec;

for(spec = (*func->specifiers).first; spec; spec = spec->next)
{
int type;

if((type = (unsigned int)ReplaceClassSpec(func->specifiers, spec, 0x0)))
ReplaceByInstancePtr(spec, &func->declarator, type);
InstDeclPassSpecifier(spec);
}
}
InstDeclPassDeclarator(func->declarator);
if(func->body)
InstDeclPassStatement(func->body);
}
else if(external->type == 1)
{
if(external->declaration)
InstDeclPassDeclaration(external->declaration);
}
}
}
