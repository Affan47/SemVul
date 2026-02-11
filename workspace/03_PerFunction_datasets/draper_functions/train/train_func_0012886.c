ProcessInstantiation(struct Instantiation * inst)
{
if(inst->members && (*inst->members).first)
{
struct MembersInit * members;

for(members = (*inst->members).first; members; members = members->next)
{
if(members->type == 0)
{
if(members->dataMembers)
{
struct MemberInit * member;

for(member = (*members->dataMembers).first; member; member = member->next)
ProcessMemberInitData(member);
}
}
else if(members->type == 1)
{
ProcessFunction((struct FunctionDefinition *)members->function);
}
}
}
}
