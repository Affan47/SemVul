SetProperty(struct __ecereNameSpace__ecere__com__Property * prop, struct __ecereNameSpace__ecere__com__Instance * object, struct __ecereNameSpace__ecere__com__DataValue * value)
{
if(object)
{
struct __ecereNameSpace__ecere__com__Class * type = prop->dataTypeClass;

if(!type)
type = prop->dataTypeClass = __ecereNameSpace__ecere__com__eSystem_FindClass(prop->_class->module, prop->dataTypeString);
if(type->type == 0 || type->type == 5 || type->type == 1)
{
((void (*)(void *, void *))(void *)prop->Set)(object, value);
}
else if(type == __ecereClass_double || !strcmp(type->dataTypeString, "double"))
{
((void (*)(void *, double))(void *)prop->Set)(object, value->d);
}
else if(type == __ecereClass_float || !strcmp(type->dataTypeString, "float"))
{
((void (*)(void *, float))(void *)prop->Set)(object, value->f);
}
else if(type->typeSize == sizeof(long long))
{
((void (*)(void *, long long))(void *)prop->Set)(object, value->i64);
}
else if(type->typeSize == sizeof(int))
{
((void (*)(void *, int))(void *)prop->Set)(object, value->i);
}
else if(type->typeSize == sizeof(short int))
{
((void (*)(void *, short))(void *)prop->Set)(object, value->s);
}
else if(type->typeSize == sizeof(unsigned char))
{
((void (*)(void *, unsigned char))(void *)prop->Set)(object, value->uc);
}
else
{
((void (*)(void *, int))(void *)prop->Set)(object, value->i);
}
}
}
