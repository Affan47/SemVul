DeclareMembers(struct __ecereNameSpace__ecere__com__Class * _class, unsigned int isMember)
{
struct __ecereNameSpace__ecere__com__DataMember * topMember = isMember ? (struct __ecereNameSpace__ecere__com__DataMember *)_class : (((void *)0));
unsigned int totalSize = 0;
struct __ecereNameSpace__ecere__com__DataMember * member;
struct Context * context = isMember ? (((void *)0)) : SetupTemplatesContext(_class);

if(!isMember && (_class->type == 1 || _class->type == 5) && _class->base->type != 1000)
DeclareMembers(_class->base, 0x0);
for(member = isMember ? topMember->members.first : _class->membersAndProperties.first; member; member = member->next)
{
if(!member->isProperty)
{
switch(member->type)
{
case 0:
{
if(!member->dataType && member->dataTypeString)
member->dataType = ProcessTypeString(member->dataTypeString, 0x0);
if(member->dataType)
DeclareType(member->dataType, 0x0, 0x0);
break;
}
case 1:
case 2:
{
DeclareMembers((struct __ecereNameSpace__ecere__com__Class *)member, 0x1);
break;
}
}
}
}
if(context)
FinishTemplatesContext(context);
return topMember ? topMember->memberID : _class->memberID;
}
