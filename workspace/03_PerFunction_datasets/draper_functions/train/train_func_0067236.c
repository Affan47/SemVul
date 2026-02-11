FindCtxClass(struct ClassDefinition * _class, int line, int charPos)
{
struct Identifier * idResult;
unsigned int insideSomething = 0x0;

if(_class->definitions)
{
struct ClassDef * def;

for(def = (*_class->definitions).first; def; def = def->next)
{
if(def->type == 1 ? InsideIncl(&def->loc, line, charPos) : Inside(&def->loc, line, charPos))
{
if(def->type != 1)
insideSomething = 0x1;
idResult = FindCtxClassDef(def, line, charPos);
if(idResult)
return idResult;
else
insideSomething = 0x0;
}
}
}
if(!insideSomething && line > _class->blockStart.start.line || (line == _class->blockStart.start.line && charPos >= _class->blockStart.start.charPos))
{
insideClass = _class->symbol->registered;
return (void *)-1;
}
return (((void *)0));
}
