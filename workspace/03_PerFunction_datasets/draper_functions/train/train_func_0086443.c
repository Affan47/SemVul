__ecereMethod___ecereNameSpace__eda__IdList_OnUnserialize(struct __ecereNameSpace__ecere__com__Class * class, struct __ecereNameSpace__ecere__com__Instance ** this, struct __ecereNameSpace__ecere__com__Instance * channel)
{
struct __ecereNameSpace__eda__IdList * __ecerePointer___ecereNameSpace__eda__IdList = (struct __ecereNameSpace__eda__IdList *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__eda__IdList->offset) : 0);
int c, count;

(*this) = (((void *)0));
__ecereMethod___ecereNameSpace__ecere__com__IOChannel_Unserialize(channel, __ecereClass_int, &count);
if(count != (0xffffffff))
{
struct __ecereNameSpace__ecere__com__Instance * idList = __ecereNameSpace__ecere__com__eInstance_New(class);

((struct __ecereNameSpace__eda__IdList *)(((char *)idList + __ecereClass___ecereNameSpace__eda__IdList->offset)))->count = count;
((struct __ecereNameSpace__eda__IdList *)(((char *)idList + __ecereClass___ecereNameSpace__eda__IdList->offset)))->ids = __ecereNameSpace__ecere__com__eSystem_New(sizeof(unsigned int) * (count));
for(c = 0; c < count; c++)
{
unsigned int id;

__ecereMethod___ecereNameSpace__ecere__com__IOChannel_Unserialize(channel, __ecereClass___ecereNameSpace__eda__Id, &id);
((struct __ecereNameSpace__eda__IdList *)(((char *)idList + __ecereClass___ecereNameSpace__eda__IdList->offset)))->ids[c] = id;
}
(*this) = idList;
}
}
