__ecereMethod___ecereNameSpace__eda__IdList_OnSerialize(struct __ecereNameSpace__ecere__com__Class * class, struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * channel)
{
struct __ecereNameSpace__eda__IdList * __ecerePointer___ecereNameSpace__eda__IdList = (struct __ecereNameSpace__eda__IdList *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__eda__IdList->offset) : 0);

if((struct __ecereNameSpace__ecere__com__Instance *)this)
{
int c;

__ecereMethod___ecereNameSpace__ecere__com__IOChannel_Serialize(channel, __ecereClass_int, &__ecerePointer___ecereNameSpace__eda__IdList->count);
for(c = 0; c < __ecerePointer___ecereNameSpace__eda__IdList->count; c++)
__ecereMethod___ecereNameSpace__ecere__com__IOChannel_Serialize(channel, __ecereClass___ecereNameSpace__eda__Id, &__ecerePointer___ecereNameSpace__eda__IdList->ids[c]);
}
else
{
unsigned int none = (0xffffffff);

__ecereMethod___ecereNameSpace__ecere__com__IOChannel_Serialize(channel, __ecereClass___ecereNameSpace__eda__Id, &none);
}
}
