__ecereNameSpace__ecere__com__eClass_FindMethod(struct __ecereNameSpace__ecere__com__Class * _class, char * name, struct __ecereNameSpace__ecere__com__Instance * module)
{
if(_class && name)
{
for(; _class; _class = _class->base)
{
struct __ecereNameSpace__ecere__com__Method * method;

if(_class->templateClass)
_class = _class->templateClass;
method = (struct __ecereNameSpace__ecere__com__Method *)__ecereMethod___ecereNameSpace__ecere__sys__BinaryTree_FindString(&_class->methods, name);
if(method && (method->memberAccess == 1 || _class->module == module || !method->dataTypeString))
{
if(!method->dataTypeString)
{
if(_class->module != module)
{
if(method->memberAccess == 1)
module = _class->module;
else
{
return (((void *)0));
}
}
}
else
{
return method;
}
}
if(_class->inheritanceAccess == 2 && _class->module != module)
break;
}
}
return (((void *)0));
}
