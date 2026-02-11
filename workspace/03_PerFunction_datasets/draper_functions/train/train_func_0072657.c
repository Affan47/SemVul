__ecereMethod_MultiStringOptionBox_OptionCheck(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * options)
{
struct MultiStringOptionBox * __ecerePointer_MultiStringOptionBox = (struct MultiStringOptionBox *)(this ? (((char *)this) + __ecereClass_MultiStringOptionBox->offset) : 0);
struct __ecereNameSpace__ecere__com__Instance * strings = *(struct __ecereNameSpace__ecere__com__Instance **)((unsigned char *)options + ((struct OptionBox *)(((char *)this + __ecereClass_OptionBox->offset)))->option);

return strings && ((struct __ecereNameSpace__ecere__com__Array *)(((char *)strings + 24)))->count;
}
