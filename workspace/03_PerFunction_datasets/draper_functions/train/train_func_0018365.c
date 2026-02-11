__ecereMethod___ecereNameSpace__eda__IdList_Includes(struct __ecereNameSpace__ecere__com__Instance * this, unsigned int id)
{
struct __ecereNameSpace__eda__IdList * __ecerePointer___ecereNameSpace__eda__IdList = (struct __ecereNameSpace__eda__IdList *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__eda__IdList->offset) : 0);

if(this)
{
int c;

for(c = 0; c < __ecerePointer___ecereNameSpace__eda__IdList->count; c++)
if(__ecerePointer___ecereNameSpace__eda__IdList->ids[c] == id)
return 0x1;
}
return 0x0;
}
