PrintName(struct Type * type, char * string, unsigned int fullName)
{
if(type->name && type->name[0])
{
if(fullName)
strcat(string, type->name);
else
{
char * name = __ecereNameSpace__ecere__sys__RSearchString(type->name, "::", strlen(type->name), 0x1, 0x0);

if(name)
name += 2;
else
name = type->name;
strcat(string, name);
}
}
}
