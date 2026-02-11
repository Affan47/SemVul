__ecereMethod___ecereNameSpace__eda__IdList_Add(struct __ecereNameSpace__ecere__com__Instance * this, unsigned int id)
{
struct __ecereNameSpace__eda__IdList * __ecerePointer___ecereNameSpace__eda__IdList = (struct __ecereNameSpace__eda__IdList *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__eda__IdList->offset) : 0);
int c;

for(c = 0; c < __ecerePointer___ecereNameSpace__eda__IdList->count; c++)
if(__ecerePointer___ecereNameSpace__eda__IdList->ids[c] == id)
break;
if(c == __ecerePointer___ecereNameSpace__eda__IdList->count)
{
__ecerePointer___ecereNameSpace__eda__IdList->ids = __ecereNameSpace__ecere__com__eSystem_Renew(__ecerePointer___ecereNameSpace__eda__IdList->ids, sizeof(unsigned int) * (__ecerePointer___ecereNameSpace__eda__IdList->count + 1));
__ecerePointer___ecereNameSpace__eda__IdList->ids[__ecerePointer___ecereNameSpace__eda__IdList->count] = id;
__ecerePointer___ecereNameSpace__eda__IdList->count++;
return 0x1;
}
return 0x0;
}
