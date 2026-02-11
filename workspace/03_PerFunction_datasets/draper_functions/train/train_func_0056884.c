__ecereMethod___ecereNameSpace__eda__Table_GUIListBoxAddRows(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * list)
{
struct __ecereNameSpace__eda__Table * __ecerePointer___ecereNameSpace__eda__Table = (struct __ecereNameSpace__eda__Table *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__eda__Table->offset) : 0);

__ecereMethod___ecereNameSpace__ecere__gui__controls__ListBox_Clear(list);
if(__ecereProp___ecereNameSpace__eda__Table_Get_rowsCount(this))
{
struct __ecereNameSpace__ecere__com__Instance * df;
struct __ecereNameSpace__ecere__com__Instance * dr;
struct __ecereNameSpace__ecere__com__Instance * r = (r = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass___ecereNameSpace__eda__Row), __ecereProp___ecereNameSpace__eda__Row_Set_tbl(r, this), r);

dr = __ecereProp___ecereNameSpace__ecere__gui__controls__ListBox_Get_firstRow(list);
while(__ecereMethod___ecereNameSpace__eda__Row_Next(r))
{
struct __ecereNameSpace__ecere__com__Instance * fld = __ecereProp___ecereNameSpace__eda__Table_Get_firstField(this);

for(df = __ecereProp___ecereNameSpace__ecere__gui__controls__ListBox_Get_firstField(list); df; df = __ecereProp___ecereNameSpace__ecere__gui__controls__DataField_Get_next(df), fld = __ecereProp___ecereNameSpace__eda__Field_Get_next(fld))
{
long long data = 0;
struct __ecereNameSpace__ecere__com__Class * type = __ecereProp___ecereNameSpace__eda__Field_Get_type(fld);

if(type->type == 3 && !type->typeSize)
{
struct __ecereNameSpace__ecere__com__Class * dataType = __ecereNameSpace__ecere__com__eSystem_FindClass(type->module, type->dataTypeString);

if(dataType)
type = dataType;
}
if(type->type == 1)
data = (long long)__ecereNameSpace__ecere__com__eSystem_New0(sizeof(unsigned char) * (type->structSize));
if(!__ecereProp___ecereNameSpace__ecere__gui__controls__DataField_Get_prev(df))
{
dr = __ecereMethod___ecereNameSpace__ecere__gui__controls__ListBox_AddRow(list);
__ecereProp___ecereNameSpace__ecere__gui__controls__DataRow_Set_tag(dr, __ecereProp___ecereNameSpace__eda__Row_Get_sysID(r));
}
((unsigned int (*)())(void *)__ecereMethod___ecereNameSpace__eda__Row_GetData)(r, fld, type, (type->type == 1) ? (void *)data : &data);
if(type->type == 1000 || type->type == 3 || type->type == 2 || type->type == 4)
__ecereMethod___ecereNameSpace__ecere__gui__controls__DataRow_SetData(dr, df, (void *)&data);
else
__ecereMethod___ecereNameSpace__ecere__gui__controls__DataRow_SetData(dr, df, (void *)data);
if(type->type == 1)
{
void * dataPtr = (void *)data;

(__ecereNameSpace__ecere__com__eSystem_Delete(dataPtr), dataPtr = 0);
}
else if(!strcmp(type->dataTypeString, "char *"))
{
char * string = (char *)data;

(__ecereNameSpace__ecere__com__eSystem_Delete(string), string = 0);
}
}
dr = __ecereProp___ecereNameSpace__ecere__gui__controls__DataRow_Get_next(dr);
}
(__ecereNameSpace__ecere__com__eInstance_DecRef(r), r = 0);
}
}
