__ecereProp_StringsBox_Get_strings(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct StringsBox * __ecerePointer_StringsBox = (struct StringsBox *)(this ? (((char *)this) + __ecereClass_StringsBox->offset) : 0);
struct __ecereNameSpace__ecere__com__Instance * array = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass___ecereNameSpace__ecere__com__Array_TPL_String_);
struct __ecereNameSpace__ecere__com__Instance * row;

for(row = __ecereProp___ecereNameSpace__ecere__gui__controls__ListBox_Get_firstRow(__ecerePointer_StringsBox->list); row; row = __ecereProp___ecereNameSpace__ecere__gui__controls__DataRow_Get_next(row))
{
char * string = __ecereProp___ecereNameSpace__ecere__gui__controls__DataRow_Get_string(row);

if(string && string[0])
((struct __ecereNameSpace__ecere__com__IteratorPointer * (*)(struct __ecereNameSpace__ecere__com__Instance *, uint64 value))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = array;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__com__Array->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__com__Container_Add])(array, (uint64)(__ecereFunction___ecereNameSpace__ecere__sys__CopyUnixPath(string)));
}
return array;
}
