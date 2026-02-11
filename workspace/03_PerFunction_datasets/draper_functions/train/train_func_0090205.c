__ecereProp___ecereNameSpace__eda__FieldBox_Get_row(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__eda__FieldBox * __ecerePointer___ecereNameSpace__eda__FieldBox = (struct __ecereNameSpace__eda__FieldBox *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__eda__FieldBox->offset) : 0);
struct __ecereNameSpace__ecere__com__Instance * result = (((void *)0));

if(__ecerePointer___ecereNameSpace__eda__FieldBox->field && __ecerePointer___ecereNameSpace__eda__FieldBox->editor)
{
if(__ecereProp___ecereNameSpace__eda__TableEditor_Get_table(__ecerePointer___ecereNameSpace__eda__FieldBox->editor) == __ecereProp___ecereNameSpace__eda__Field_Get_table(__ecerePointer___ecereNameSpace__eda__FieldBox->field))
result = ((struct __ecereNameSpace__eda__TableEditor *)(((char *)__ecerePointer___ecereNameSpace__eda__FieldBox->editor + __ecereClass___ecereNameSpace__eda__TableEditor->offset)))->editRow;
else if(((struct __ecereNameSpace__eda__TableEditor *)(((char *)__ecerePointer___ecereNameSpace__eda__FieldBox->editor + __ecereClass___ecereNameSpace__eda__TableEditor->offset)))->lookups)
{
struct __ecereNameSpace__ecere__com__Instance * lookup = (__extension__ ({
struct __ecereNameSpace__ecere__com__Iterator __internalIterator =
{
((struct __ecereNameSpace__eda__TableEditor * )(((char * )__ecerePointer___ecereNameSpace__eda__FieldBox->editor + __ecereClass___ecereNameSpace__eda__TableEditor->offset)))->lookups, 0
};

__ecereMethod___ecereNameSpace__ecere__com__Iterator_Index(&__internalIterator, (uint64)(((uint64)(__ecereProp___ecereNameSpace__eda__Field_Get_table(__ecerePointer___ecereNameSpace__eda__FieldBox->field)))), 0x0);
((struct __ecereNameSpace__ecere__com__Instance *)__ecereProp___ecereNameSpace__ecere__com__Iterator_Get_data(&__internalIterator));
}));

if(((struct __ecereNameSpace__eda__Lookup *)(((char *)lookup + __ecereClass___ecereNameSpace__eda__Lookup->offset)))->valueField && ((struct __ecereNameSpace__eda__Lookup *)(((char *)lookup + __ecereClass___ecereNameSpace__eda__Lookup->offset)))->findField && ((struct __ecereNameSpace__eda__Lookup *)(((char *)lookup + __ecereClass___ecereNameSpace__eda__Lookup->offset)))->row && !__ecereProp___ecereNameSpace__eda__Row_Get_nil(((struct __ecereNameSpace__eda__Lookup *)(((char *)lookup + __ecereClass___ecereNameSpace__eda__Lookup->offset)))->row))
result = ((struct __ecereNameSpace__eda__Lookup *)(((char *)lookup + __ecereClass___ecereNameSpace__eda__Lookup->offset)))->row;
}
}
return result;
}
