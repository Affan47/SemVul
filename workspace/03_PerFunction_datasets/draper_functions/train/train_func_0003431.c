__ecereMethod___ecereNameSpace__eda__TableEditor_AddTableEditor(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * tableEditor)
{
struct __ecereNameSpace__eda__TableEditor * __ecerePointer___ecereNameSpace__eda__TableEditor = (struct __ecereNameSpace__eda__TableEditor *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__eda__TableEditor->offset) : 0);

__ecereNameSpace__eda__DebugLn(__ecereClass_char__PTR_, "TableEditor::AddTableEditor", (void *)0);
if(!((struct __ecereNameSpace__ecere__com__IteratorPointer * (*)(struct __ecereNameSpace__ecere__com__Instance *, uint64 value))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = __ecerePointer___ecereNameSpace__eda__TableEditor->tableEditors;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__com__Array->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__com__Container_Find])(__ecerePointer___ecereNameSpace__eda__TableEditor->tableEditors, (uint64)(tableEditor)))
{
((struct __ecereNameSpace__ecere__com__IteratorPointer * (*)(struct __ecereNameSpace__ecere__com__Instance *, uint64 value))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = __ecerePointer___ecereNameSpace__eda__TableEditor->tableEditors;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__com__Array->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__com__Container_Add])(__ecerePointer___ecereNameSpace__eda__TableEditor->tableEditors, (uint64)(tableEditor));
tableEditor->_refCount++;
}
else
__ecereNameSpace__eda__DebugLn(__ecereClass_char__PTR_, "   TableEditor instance already added", (void *)0);
}
