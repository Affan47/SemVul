__ecereMethod_HTMLView_OnPostCreate(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct HTMLView * __ecerePointer_HTMLView = (struct HTMLView *)(this ? (((char *)this) + __ecereClass_HTMLView->offset) : 0);

if(__ecerePointer_HTMLView->location)
__ecereMethod_HTMLView_Open(this, __ecerePointer_HTMLView->location, (((void *)0)));
return 0x1;
}
