__ecereMethod_Designer_ObjectContainsCode(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__ObjectInfo * object)
{
struct Designer * __ecerePointer_Designer = (struct Designer *)(this ? (((char *)this) + __ecereClass_Designer->offset) : 0);

if(object->instCode)
{
struct MembersInit * members;

if(object->instCode->members)
{
for(members = (*object->instCode->members).first; members; members = members->next)
{
if(members->type == 1)
{
{
return 0x1;
}
}
}
}
}
return 0x0;
}
