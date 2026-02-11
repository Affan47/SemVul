MkClassTypeSymbol(struct Symbol * symbol)
{
if(symbol)
{
struct Type * type = (type = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass_Type), type->kind = 8, type->_class = symbol, type);

if(!type->_class)
{
type->kind = 3;
}
type->refCount = 1;
return type;
}
return (((void *)0));
}
