__ecereMethod_HTMLView_OnResize(struct __ecereNameSpace__ecere__com__Instance * this, int width, int height)
{
struct HTMLView * __ecerePointer_HTMLView = (struct HTMLView *)(this ? (((char *)this) + __ecereClass_HTMLView->offset) : 0);

if(((struct HTMLFile *)(((char *)__ecerePointer_HTMLView->html + __ecereClass_HTMLFile->offset)))->body)
{
__ecereMethod_HTMLView_ComputeMinSizes(this);
__ecereMethod_HTMLView_ComputeSizes(this);
__ecereMethod_HTMLView_PositionForms(this);
}
}
