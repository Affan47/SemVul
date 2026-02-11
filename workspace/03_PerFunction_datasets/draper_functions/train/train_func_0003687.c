FreeDeclarator(struct Declarator * decl)
{
if(decl->declarator)
FreeDeclarator(decl->declarator);
switch(decl->type)
{
case 0:
if(decl->structDecl.exp)
FreeExpression(decl->structDecl.exp);
if(decl->structDecl.posExp)
FreeExpression(decl->structDecl.posExp);
(__ecereNameSpace__ecere__com__eSystem_Delete(decl->structDecl.attrib), decl->structDecl.attrib = 0);
break;
case 1:
FreeIdentifier(decl->identifier);
break;
case 2:
break;
case 3:
if(decl->array.exp)
FreeExpression(decl->array.exp);
if(decl->array.enumClass)
FreeSpecifier(decl->array.enumClass);
break;
case 4:
FreeList(decl->function.parameters, FreeTypeName);
break;
case 5:
if(decl->pointer.pointer)
FreePointer(decl->pointer.pointer);
break;
case 6:
case 7:
(__ecereNameSpace__ecere__com__eSystem_Delete(decl->extended.extended), decl->extended.extended = 0);
break;
}
((decl ? (__ecereClass_Declarator->Destructor ? __ecereClass_Declarator->Destructor(decl) : 0, __ecereNameSpace__ecere__com__eSystem_Delete(decl)) : 0), decl = 0);
}
