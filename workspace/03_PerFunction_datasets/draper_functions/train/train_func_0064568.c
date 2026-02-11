FindCtxDeclaration(struct Declaration * decl, int line, int charPos)
{
struct Identifier * idResult;

switch(decl->type)
{
case 0:
{
struct Specifier * spec;

if(decl->specifiers)
{
for(spec = (*decl->specifiers).first; spec; spec = spec->next)
{
if(InsideIncl(&spec->loc, line, charPos))
{
idResult = FindCtxSpecifier(spec, line, charPos);
if(idResult)
return idResult;
}
}
}
break;
}
case 1:
{
if(decl->specifiers)
{
struct Specifier * s;

for(s = (*decl->specifiers).first; s; s = s->next)
{
if(InsideIncl(&s->loc, line, charPos))
{
idResult = FindCtxSpecifier(s, line, charPos);
if(idResult)
return idResult;
}
}
}
if(decl->declarators && (*decl->declarators).first)
{
struct InitDeclarator * d;

for(d = (*decl->declarators).first; d; d = d->next)
{
if(InsideIncl(&d->loc, line, charPos))
{
idResult = FindCtxInitDeclarator(d, line, charPos);
if(idResult)
return idResult;
}
}
}
break;
}
case 2:
if(InsideIncl(&decl->inst->loc, line, charPos))
return FindCtxInstance(decl->inst, line, charPos);
break;
}
return (((void *)0));
}
