__ecereProp___ecereNameSpace__eda__FieldDataBox_Set_editor(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * value)
{
struct __ecereNameSpace__eda__FieldDataBox * __ecerePointer___ecereNameSpace__eda__FieldDataBox = (struct __ecereNameSpace__eda__FieldDataBox *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__eda__FieldDataBox->offset) : 0);

__ecereProp___ecereNameSpace__ecere__gui__Window_Set_parent(this, ((struct __ecereNameSpace__eda__EditSection *)(((char *)value + __ecereClass___ecereNameSpace__eda__EditSection->offset)))->editArea);
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_master(this, value);
__ecereMethod___ecereNameSpace__eda__EditSection_AddFieldEditor(value, this);
__ecerePointer___ecereNameSpace__eda__FieldDataBox->row = ((struct __ecereNameSpace__eda__EditSection *)(((char *)value + __ecereClass___ecereNameSpace__eda__EditSection->offset)))->editRow;
__ecereNameSpace__ecere__com__eInstance_FireSelfWatchers(this, __ecereProp___ecereNameSpace__eda__FieldDataBox_editor), __ecereNameSpace__ecere__com__eInstance_FireSelfWatchers(this, __ecerePropM___ecereNameSpace__eda__FieldDataBox_editor);
}
