__ecereMethod___ecereNameSpace__ecere__gui__controls__ListBox_FindSubStringi(struct __ecereNameSpace__ecere__com__Instance * this, char * subString)
{
struct __ecereNameSpace__ecere__gui__controls__ListBox * __ecerePointer___ecereNameSpace__ecere__gui__controls__ListBox = (struct __ecereNameSpace__ecere__gui__controls__ListBox *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__ListBox->offset) : 0);
struct __ecereNameSpace__ecere__com__Instance * field;
unsigned int checkNextField = 0x1;
int len = subString ? strlen(subString) : 0;
struct __ecereNameSpace__ecere__com__Instance * result = (((void *)0));
char * bestResult = (((void *)0));
int bestLen = 0;

if(len)
{
for(field = __ecerePointer___ecereNameSpace__ecere__gui__controls__ListBox->fields.first; field; field = __ecereProp___ecereNameSpace__ecere__gui__controls__DataField_Get_next(field))
{
if(__ecereProp___ecereNameSpace__ecere__gui__controls__DataField_Get_dataType(field)->_vTbl[__ecereVMethodID_class_OnGetString])
{
struct __ecereNameSpace__ecere__com__Instance * row;

for(row = __ecerePointer___ecereNameSpace__ecere__gui__controls__ListBox->rows.first; row; row = __ecereMethod___ecereNameSpace__ecere__gui__controls__DataRow_GetNextRow(row))
{
if(!((struct __ecereNameSpace__ecere__gui__controls__DataRow *)(((char *)row + __ecereClass___ecereNameSpace__ecere__gui__controls__DataRow->offset)))->noneRow)
{
void * data = (void * )__ecereMethod___ecereNameSpace__ecere__gui__controls__DataRow_GetData(row, field);
char tempString[1024] = "";
unsigned int needClass = 0x0;
char * string = ((char * (*)(void *, void *, char *, void *, unsigned int *))(void *)__ecereProp___ecereNameSpace__ecere__gui__controls__DataField_Get_dataType(field)->_vTbl[__ecereVMethodID_class_OnGetString])(__ecereProp___ecereNameSpace__ecere__gui__controls__DataField_Get_dataType(field), data, tempString, (((void *)0)), &needClass);

if(string && string[0])
checkNextField = 0x0;
if(string && string[0])
{
int stringLen = strlen(string);

if(!(strncasecmp)(string, subString, ((len < stringLen) ? len : stringLen)))
{
if(bestLen < ((len < stringLen) ? len : stringLen))
bestResult = 0;
if(!bestResult || (strcasecmp)(string, bestResult) < 0)
{
bestLen = ((len < stringLen) ? len : stringLen);
bestResult = string;
result = row;
}
}
}
}
}
}
if(!checkNextField)
break;
}
}
return result;
}
