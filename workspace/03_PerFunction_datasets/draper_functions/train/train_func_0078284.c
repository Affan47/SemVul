__ecereProp___ecereNameSpace__eda__TableEditor_Set_searchFields(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * value)
{
struct __ecereNameSpace__eda__TableEditor * __ecerePointer___ecereNameSpace__eda__TableEditor = (struct __ecereNameSpace__eda__TableEditor *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__eda__TableEditor->offset) : 0);
struct __ecereNameSpace__ecere__com__Instance * searchTable = (searchTable = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass___ecereNameSpace__eda__StringSearchTable), ((struct __ecereNameSpace__eda__StringSearchTable *)(((char *)searchTable + __ecereClass___ecereNameSpace__eda__StringSearchTable->offset)))->table = __ecerePointer___ecereNameSpace__eda__TableEditor->table, ((struct __ecereNameSpace__eda__StringSearchTable *)(((char *)searchTable + __ecereClass___ecereNameSpace__eda__StringSearchTable->offset)))->idField = __ecerePointer___ecereNameSpace__eda__TableEditor->idField, ((struct __ecereNameSpace__eda__StringSearchTable *)(((char *)searchTable + __ecereClass___ecereNameSpace__eda__StringSearchTable->offset)))->searchFields = value, searchTable);

__ecereNameSpace__eda__DebugLn(__ecereClass_char__PTR_, "TableEditor::searchFields|set", (void *)0);
__ecereProp___ecereNameSpace__eda__TableEditor_Set_searchTables(this, __extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __ecereInstance1 = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass___ecereNameSpace__ecere__com__Array_TPL_eda__StringSearchTable_);

__ecereProp___ecereNameSpace__ecere__com__Container_Set_copySrc(__ecereInstance1, ((struct __ecereNameSpace__ecere__com__Instance *)&__extension__ (struct __ecereNameSpace__ecere__com__BuiltInContainer)
{
__ecereClass___ecereNameSpace__ecere__com__BuiltInContainer->_vTbl, __ecereClass___ecereNameSpace__ecere__com__BuiltInContainer, 0, __extension__ (struct __ecereNameSpace__ecere__com__Instance * [])
{
searchTable
}, 1, __ecereClass___ecereNameSpace__eda__StringSearchTable
})), __ecereInstance1;
}));
__ecereNameSpace__ecere__com__eInstance_FireSelfWatchers(this, __ecereProp___ecereNameSpace__eda__TableEditor_searchFields), __ecereNameSpace__ecere__com__eInstance_FireSelfWatchers(this, __ecerePropM___ecereNameSpace__eda__TableEditor_searchFields);
}
