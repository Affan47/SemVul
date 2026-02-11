OutputType(struct __ecereNameSpace__ecere__com__Instance * f, struct Type * type, unsigned int outputName)
{
if(type)
{
switch(type->kind)
{
case 0:
__ecereMethod___ecereNameSpace__ecere__sys__File_Printf(f, "void");
break;
case 1:
if(!type->isSigned)
__ecereMethod___ecereNameSpace__ecere__sys__File_Printf(f, "unsigned ");
__ecereMethod___ecereNameSpace__ecere__sys__File_Printf(f, "char");
break;
case 2:
if(!type->isSigned)
__ecereMethod___ecereNameSpace__ecere__sys__File_Printf(f, "unsigned ");
__ecereMethod___ecereNameSpace__ecere__sys__File_Printf(f, "short");
break;
case 3:
if(!type->isSigned)
__ecereMethod___ecereNameSpace__ecere__sys__File_Printf(f, "unsigned ");
__ecereMethod___ecereNameSpace__ecere__sys__File_Printf(f, "int");
break;
case 4:
if(!type->isSigned)
__ecereMethod___ecereNameSpace__ecere__sys__File_Printf(f, "unsigned ");
__ecereMethod___ecereNameSpace__ecere__sys__File_Printf(f, "__int64");
break;
case 5:
if(!type->isSigned)
__ecereMethod___ecereNameSpace__ecere__sys__File_Printf(f, "unsigned ");
__ecereMethod___ecereNameSpace__ecere__sys__File_Printf(f, "long");
break;
case 6:
__ecereMethod___ecereNameSpace__ecere__sys__File_Printf(f, "float");
break;
case 7:
__ecereMethod___ecereNameSpace__ecere__sys__File_Printf(f, "double");
break;
case 8:
{
if(type->_class && !strcmp(type->_class->string, "class"))
{
switch(type->classObjectType)
{
case 3:
__ecereMethod___ecereNameSpace__ecere__sys__File_Printf(f, "any_object");
break;
default:
__ecereMethod___ecereNameSpace__ecere__sys__File_Printf(f, "typed_object");
break;
}
if(type->byReference)
__ecereMethod___ecereNameSpace__ecere__sys__File_Printf(f, " &");
}
else
__ecereMethod___ecereNameSpace__ecere__sys__File_Printf(f, type->_class->shortName ? type->_class->shortName : type->_class->string);
break;
}
case 9:
break;
case 10:
break;
case 11:
break;
case 12:
OutputType(f, type->type, 0x0);
break;
case 13:
OutputType(f, type->type, 0x0);
__ecereMethod___ecereNameSpace__ecere__sys__File_Printf(f, " *");
break;
case 14:
__ecereMethod___ecereNameSpace__ecere__sys__File_Printf(f, "...");
break;
case 15:
break;
case 16:
break;
}
if(outputName)
{
if(type->name)
{
__ecereMethod___ecereNameSpace__ecere__sys__File_Printf(f, " ");
__ecereMethod___ecereNameSpace__ecere__sys__File_Printf(f, type->name);
}
}
if(type->kind == 12)
{
__ecereMethod___ecereNameSpace__ecere__sys__File_Printf(f, "[");
__ecereMethod___ecereNameSpace__ecere__sys__File_Printf(f, "%d", type->arraySize);
__ecereMethod___ecereNameSpace__ecere__sys__File_Printf(f, "]");
}
}
}
