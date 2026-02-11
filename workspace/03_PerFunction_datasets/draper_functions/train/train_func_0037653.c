CopyMembersInit(struct MembersInit * members)
{
struct __ecereNameSpace__ecere__sys__OldList * list = (((void *)0));

switch(members->type)
{
case 0:
{
if(members)
{
struct MemberInit * member;

list = MkList();
for(member = (*members->dataMembers).first; member; member = member->next)
ListAdd(list, CopyMemberInit(member));
}
}
}
return MkMembersInitList(list);
}
