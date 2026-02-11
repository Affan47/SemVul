ProcessTemplateParameterType(struct TemplateParameter * param)
{
if(param && param->type == 0 && (param->dataType || param->dataTypeString))
{
if(!param->baseType)
{
if(param->dataTypeString)
param->baseType = ProcessTypeString(param->dataTypeString, 0x0);
else
param->baseType = ProcessType(param->dataType->specifiers, param->dataType->decl);
}
return param->baseType;
}
return (((void *)0));
}
