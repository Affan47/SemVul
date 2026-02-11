ProcessDeclaration(struct Declaration * decl)
{
switch(decl->type)
{
case 1:
{
if(decl->declarators)
{
struct InitDeclarator * d;

for(d = (*decl->declarators).first; d; d = d->next)
{
if(d->initializer)
ProcessInitializer(d->initializer);
}
}
break;
}
}
}
