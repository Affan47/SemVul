__ecereInstMeth_StringArrayOptionTools_FinalizeLoading__00000006(struct __ecereNameSpace__ecere__com__Instance * this, int option, struct __ecereNameSpace__ecere__com__Instance * optionTempStrings, struct __ecereNameSpace__ecere__com__Instance * output)
{
struct StringArrayOptionTools * __ecerePointer_StringArrayOptionTools = (struct StringArrayOptionTools *)(this ? (((char *)this) + __ecereClass_StringArrayOptionTools->offset) : 0);

if(((struct GenericOptionTools *)(((char *)this + __ecereClass_GenericOptionTools->offset)))->mergeValues)
{
struct __ecereNameSpace__ecere__com__Instance * tempStrings = ((struct __ecereNameSpace__ecere__com__Instance **)((struct __ecereNameSpace__ecere__com__Array *)(((char *)optionTempStrings + 24)))->array)[option];
struct __ecereNameSpace__ecere__com__Instance ** strings = (struct __ecereNameSpace__ecere__com__Instance **)((unsigned char *)output + option);

if(*strings)
{
((void (*)(struct __ecereNameSpace__ecere__com__Instance *))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = (*strings);

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__com__Array->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__com__Container_Free])((*strings));
(__ecereNameSpace__ecere__com__eInstance_DecRef(*strings), *strings = 0);
}
if(tempStrings && ((struct __ecereNameSpace__ecere__com__Array *)(((char *)tempStrings + 24)))->count)
{
*strings = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass___ecereNameSpace__ecere__com__Array_TPL_String_);
((void (*)(struct __ecereNameSpace__ecere__com__Instance *, struct __ecereNameSpace__ecere__com__Instance * source))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = (*strings);

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__com__Array->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__com__Container_Copy])((*strings), (void *)tempStrings);
}
(__ecereNameSpace__ecere__com__eInstance_DecRef(tempStrings), tempStrings = 0);
}
}
