FreeClassDef(struct ClassDef * def)
{
switch(def->type)
{
case 2:
if(def->decl)
FreeDeclaration(def->decl);
break;
case 1:
{
FreeList(def->defProperties, FreeMemberInit);
break;
}
case 0:
if(def->function)
FreeClassFunction(def->function);
break;
case 3:
if(def->propertyDef)
FreeProperty(def->propertyDef);
break;
case 10:
if(def->propertyDef)
FreeProperty(def->propertyDef);
break;
case 13:
break;
case 9:
{
if(def->decl)
FreeDeclaration(def->decl);
break;
}
case 5:
{
(__ecereNameSpace__ecere__com__eSystem_Delete(def->designer), def->designer = 0);
break;
}
case 7:
break;
case 6:
break;
case 11:
if(def->id)
FreeIdentifier(def->id);
if(def->initializer)
FreeInitializer(def->initializer);
break;
case 8:
{
if(def->defaultProperty)
FreeIdentifier(def->defaultProperty);
break;
}
case 12:
break;
case 4:
{
if(def->propertyWatch)
FreePropertyWatch(def->propertyWatch);
break;
}
}
((def ? (__ecereClass_ClassDef->Destructor ? __ecereClass_ClassDef->Destructor(def) : 0, __ecereNameSpace__ecere__com__eSystem_Delete(def)) : 0), def = 0);
}
