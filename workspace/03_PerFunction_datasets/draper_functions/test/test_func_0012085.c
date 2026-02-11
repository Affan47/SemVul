__ecereNameSpace__ecere__com__Enum_OnGetString(struct __ecereNameSpace__ecere__com__Class * _class, int * data, char * tempString, void * fieldData, unsigned int * needClass)
{
struct __ecereNameSpace__ecere__sys__NamedLink * item = (((void *)0));
struct __ecereNameSpace__ecere__com__Class * b;

for(b = _class; !item && b && b->type == 4; b = b->base)
{
struct __ecereNameSpace__ecere__com__EnumClassData * enumeration = (struct __ecereNameSpace__ecere__com__EnumClassData *)b->data;

for(item = enumeration->values.first; item; item = item->next)
if((int)item->data == *data)
break;
}
if(item)
{
strcpy(tempString, item->name);
if(!needClass || !*needClass)
tempString[0] = (char)toupper(tempString[0]);
return tempString;
}
else
return (((void *)0));
}
