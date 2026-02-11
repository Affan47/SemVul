CreateFireWatcher(struct __ecereNameSpace__ecere__com__Property * prop, struct Expression * object, struct Statement * stmt)
{
char propName[1024], propNameM[1024];
char getName[1024], setName[1024];
struct __ecereNameSpace__ecere__sys__OldList * args;

DeclareProperty(prop, setName, getName);
strcpy(propName, "__ecereProp_");
FullClassNameCat(propName, prop->_class->fullName, 0x0);
strcat(propName, "_");
FullClassNameCat(propName, prop->name, 0x1);
MangleClassName(propName);
strcpy(propNameM, "__ecerePropM_");
FullClassNameCat(propNameM, prop->_class->fullName, 0x0);
strcat(propNameM, "_");
FullClassNameCat(propNameM, prop->name, 0x1);
MangleClassName(propNameM);
if(prop->isWatchable)
{
args = MkList();
ListAdd(args, object ? CopyExpression(object) : MkExpIdentifier(MkIdentifier("this")));
ListAdd(args, MkExpIdentifier(MkIdentifier(propName)));
ListAdd(stmt->expressions, MkExpCall(MkExpIdentifier(MkIdentifier("ecere::com::eInstance_FireWatchers")), args));
args = MkList();
ListAdd(args, object ? CopyExpression(object) : MkExpIdentifier(MkIdentifier("this")));
ListAdd(args, MkExpIdentifier(MkIdentifier(propNameM)));
ListAdd(stmt->expressions, MkExpCall(MkExpIdentifier(MkIdentifier("ecere::com::eInstance_FireWatchers")), args));
}
{
args = MkList();
ListAdd(args, object ? CopyExpression(object) : MkExpIdentifier(MkIdentifier("this")));
ListAdd(args, MkExpIdentifier(MkIdentifier(propName)));
ListAdd(stmt->expressions, MkExpCall(MkExpIdentifier(MkIdentifier("ecere::com::eInstance_FireSelfWatchers")), args));
args = MkList();
ListAdd(args, object ? CopyExpression(object) : MkExpIdentifier(MkIdentifier("this")));
ListAdd(args, MkExpIdentifier(MkIdentifier(propNameM)));
ListAdd(stmt->expressions, MkExpCall(MkExpIdentifier(MkIdentifier("ecere::com::eInstance_FireSelfWatchers")), args));
}
if(curFunction->propSet && !strcmp(curFunction->propSet->string, prop->name) && (!object || (object->type == 0 && !strcmp(object->identifier->string, "this"))))
curFunction->propSet->fireWatchersDone = 0x1;
}
