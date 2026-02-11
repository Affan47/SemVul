GetTypeSpecs(struct Type * type, struct __ecereNameSpace__ecere__sys__OldList * specs)
{
if(!type->isSigned)
ListAdd(specs, MkSpecifier(296));
switch(type->kind)
{
case 8:
{
if(type->_class->registered)
{
if(!type->_class->registered->dataType)
type->_class->registered->dataType = ProcessTypeString(type->_class->registered->dataTypeString, 0x0);
GetTypeSpecs(type->_class->registered->dataType, specs);
}
break;
}
case 7:
ListAdd(specs, MkSpecifier(298));
break;
case 6:
ListAdd(specs, MkSpecifier(297));
break;
case 1:
ListAdd(specs, MkSpecifier(289));
break;
case 2:
ListAdd(specs, MkSpecifier(290));
break;
case 4:
ListAdd(specs, MkSpecifier(293));
break;
case 3:
default:
ListAdd(specs, MkSpecifier(291));
break;
}
}
