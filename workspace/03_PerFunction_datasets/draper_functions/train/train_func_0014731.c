__ecereProp___ecereNameSpace__eda__TableEditor_Set_searchTables(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * value)
{
struct __ecereNameSpace__eda__TableEditor * __ecerePointer___ecereNameSpace__eda__TableEditor = (struct __ecereNameSpace__eda__TableEditor *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__eda__TableEditor->offset) : 0);

value->_refCount++;
{
struct __ecereNameSpace__ecere__com__Instance ** t;
struct __ecereNameSpace__ecere__com__Instance * __internalArray = (value);

for(t = (struct __ecereNameSpace__ecere__com__Instance **)((struct __ecereNameSpace__ecere__com__Array *)(((char *)__internalArray + 24)))->array; t < (struct __ecereNameSpace__ecere__com__Instance **)((struct __ecereNameSpace__ecere__com__Array *)(((char *)__internalArray + 24)))->array + ((struct __ecereNameSpace__ecere__com__Array *)(((char *)__internalArray + 24)))->count; t++)
{
(*t)->_refCount++;
}
}
__ecereNameSpace__eda__DebugLn(__ecereClass_char__PTR_, "TableEditor::searchTables|set", (void *)0);
if(__ecerePointer___ecereNameSpace__eda__TableEditor->searchTables)
((void (*)(struct __ecereNameSpace__ecere__com__Instance *))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = __ecerePointer___ecereNameSpace__eda__TableEditor->searchTables;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__com__Array->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__com__Container_Free])(__ecerePointer___ecereNameSpace__eda__TableEditor->searchTables);
(__ecereNameSpace__ecere__com__eInstance_DecRef(__ecerePointer___ecereNameSpace__eda__TableEditor->searchTables), __ecerePointer___ecereNameSpace__eda__TableEditor->searchTables = 0);
__ecerePointer___ecereNameSpace__eda__TableEditor->searchTables = value;
__ecereNameSpace__ecere__com__eInstance_FireSelfWatchers(this, __ecereProp___ecereNameSpace__eda__TableEditor_searchTables), __ecereNameSpace__ecere__com__eInstance_FireSelfWatchers(this, __ecerePropM___ecereNameSpace__eda__TableEditor_searchTables);
}
