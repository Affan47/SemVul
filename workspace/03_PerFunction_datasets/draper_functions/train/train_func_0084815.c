__ecereMethod___ecereNameSpace__eda__EDBTable_CreateRow(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__eda__EDBTable * __ecerePointer___ecereNameSpace__eda__EDBTable = (struct __ecereNameSpace__eda__EDBTable *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__eda__EDBTable->offset) : 0);

return __extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __ecereInstance1 = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass___ecereNameSpace__eda__EDBRow);

((struct __ecereNameSpace__eda__EDBRow *)(((char *)__ecereInstance1 + __ecereClass___ecereNameSpace__eda__EDBRow->offset)))->tbl = __ecerePointer___ecereNameSpace__eda__EDBTable->dbTable, ((struct __ecereNameSpace__eda__EDBRow *)(((char *)__ecereInstance1 + __ecereClass___ecereNameSpace__eda__EDBRow->offset)))->index = __ecerePointer___ecereNameSpace__eda__EDBTable->index, __ecereProp___ecereNameSpace__eda__EDBRow_Set_num(__ecereInstance1, 0), __ecereInstance1;
});
}
