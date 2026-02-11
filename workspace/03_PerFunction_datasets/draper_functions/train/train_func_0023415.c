__ecereMethod___ecereNameSpace__eda__EDBTable_AddField(struct __ecereNameSpace__ecere__com__Instance * this, const char * name, struct __ecereNameSpace__ecere__com__Class * type, int length)
{
struct __ecereNameSpace__eda__EDBTable * __ecerePointer___ecereNameSpace__eda__EDBTable = (struct __ecereNameSpace__eda__EDBTable *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__eda__EDBTable->offset) : 0);
struct __ecereNameSpace__ecere__com__Instance * edb = __ecerePointer___ecereNameSpace__eda__EDBTable->dbTable->db;
struct __ecereNameSpace__ecere__com__Instance * field = (field = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass___ecereNameSpace__eda__EDBField), ((struct __ecereNameSpace__eda__EDBField *)(((char *)field + __ecereClass___ecereNameSpace__eda__EDBField->offset)))->tbl = __ecerePointer___ecereNameSpace__eda__EDBTable->dbTable, ((struct __ecereNameSpace__eda__EDBField *)(((char *)field + __ecereClass___ecereNameSpace__eda__EDBField->offset)))->name = __ecereFunction___ecereNameSpace__ecere__sys__CopyString(name), ((struct __ecereNameSpace__eda__EDBField *)(((char *)field + __ecereClass___ecereNameSpace__eda__EDBField->offset)))->type = type, ((struct __ecereNameSpace__eda__EDBField *)(((char *)field + __ecereClass___ecereNameSpace__eda__EDBField->offset)))->length = length, field);
struct __ecereNameSpace__eda__DBTable * fieldsTable = __ecerePointer___ecereNameSpace__eda__EDBTable->dbTable->fieldsTable;

field->_refCount++;
if(!fieldsTable)
fieldsTable = __ecerePointer___ecereNameSpace__eda__EDBTable->dbTable->fieldsTable = __ecereMethod___ecereNameSpace__eda__EDBDatabase_GetDBTable(edb, __ecerePointer___ecereNameSpace__eda__EDBTable->dbTable->apathFields, (((unsigned int)(6))));
__ecereNameSpace__eda__RowsCountFileEdit(((struct __ecereNameSpace__eda__EDBDatabase *)(((char *)edb + __ecereClass___ecereNameSpace__eda__EDBDatabase->offset)))->archive, __ecerePointer___ecereNameSpace__eda__EDBTable->dbTable->apathFields, 1, &fieldsTable->allocatedRowsCount, &fieldsTable->deletedRowsCount, &fieldsTable->rowsCountPosition);
fieldsTable->rowsCount = fieldsTable->allocatedRowsCount - fieldsTable->deletedRowsCount;
fieldsTable->rowPositions = __ecereNameSpace__ecere__com__eSystem_Renew0(fieldsTable->rowPositions, sizeof(unsigned int) * (fieldsTable->allocatedRowsCount));
__ecereMethod___ecereNameSpace__ecere__sys__OldList_Add(&__ecerePointer___ecereNameSpace__eda__EDBTable->dbTable->fields, field);
__ecereProp___ecereNameSpace__eda__EDBField_Set_num(field, __ecerePointer___ecereNameSpace__eda__EDBTable->dbTable->fields.count);
__ecereMethod___ecereNameSpace__eda__EDBField_Write(field);
return field;
}
