__ecereMethod___ecereNameSpace__eda__FieldBox_Load(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__eda__FieldBox * __ecerePointer___ecereNameSpace__eda__FieldBox = (struct __ecereNameSpace__eda__FieldBox *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__eda__FieldBox->offset) : 0);
struct __ecereNameSpace__ecere__com__Instance * row = __ecereProp___ecereNameSpace__eda__FieldBox_Get_row(this);

if(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_visible(this) && row)
{
((void (*)(struct __ecereNameSpace__ecere__com__Instance *, void * newData, unsigned int closingDropDown))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = this;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__eda__FieldBox->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__gui__controls__DataBox_SetData])(this, (((void *)0)), 0x0);
((unsigned int (*)())(void *)__ecereMethod___ecereNameSpace__eda__Row_GetData)(row, __ecerePointer___ecereNameSpace__eda__FieldBox->field, __ecereProp___ecereNameSpace__eda__Field_Get_type(__ecerePointer___ecereNameSpace__eda__FieldBox->field), ((struct __ecereNameSpace__ecere__gui__controls__DataBox *)(((char *)this + __ecereClass___ecereNameSpace__ecere__gui__controls__DataBox->offset)))->data);
if(!__ecerePointer___ecereNameSpace__eda__FieldBox->dataHolder && ((struct __ecereNameSpace__ecere__gui__controls__DataBox *)(((char *)this + __ecereClass___ecereNameSpace__ecere__gui__controls__DataBox->offset)))->type && (((struct __ecereNameSpace__ecere__gui__controls__DataBox *)(((char *)this + __ecereClass___ecereNameSpace__ecere__gui__controls__DataBox->offset)))->type->type == 5 || ((struct __ecereNameSpace__ecere__gui__controls__DataBox *)(((char *)this + __ecereClass___ecereNameSpace__ecere__gui__controls__DataBox->offset)))->type->type == 0))
{
if(__ecereNameSpace__ecere__com__eClass_IsDerived(((struct __ecereNameSpace__ecere__gui__controls__DataBox *)(((char *)this + __ecereClass___ecereNameSpace__ecere__gui__controls__DataBox->offset)))->type, __ecereClass_String))
__ecerePointer___ecereNameSpace__eda__FieldBox->dataHolder = (long long)__ecereFunction___ecereNameSpace__ecere__sys__CopyString("");
else
__ecerePointer___ecereNameSpace__eda__FieldBox->dataHolder = (long long)__ecereNameSpace__ecere__com__eInstance_New(((struct __ecereNameSpace__ecere__gui__controls__DataBox *)(((char *)this + __ecereClass___ecereNameSpace__ecere__gui__controls__DataBox->offset)))->type);
((struct __ecereNameSpace__ecere__gui__controls__DataBox *)(((char *)this + __ecereClass___ecereNameSpace__ecere__gui__controls__DataBox->offset)))->data = (void *)&__ecerePointer___ecereNameSpace__eda__FieldBox->dataHolder;
}
__ecereMethod___ecereNameSpace__ecere__gui__controls__DataBox_Refresh(this);
}
}
