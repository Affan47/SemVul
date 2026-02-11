__ecereMethod___ecereNameSpace__ecere__gui__controls__DataRow_GetLastRow(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__ecere__gui__controls__DataRow * __ecerePointer___ecereNameSpace__ecere__gui__controls__DataRow = (struct __ecereNameSpace__ecere__gui__controls__DataRow *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__DataRow->offset) : 0);
struct __ecereNameSpace__ecere__com__Instance * row = this;

while(row && !__ecereProp___ecereNameSpace__ecere__gui__controls__DataRow_Get_collapsed(row) && ((struct __ecereNameSpace__ecere__gui__controls__DataRow *)(((char *)row + __ecereClass___ecereNameSpace__ecere__gui__controls__DataRow->offset)))->subRows.last)
row = ((struct __ecereNameSpace__ecere__gui__controls__DataRow *)(((char *)row + __ecereClass___ecereNameSpace__ecere__gui__controls__DataRow->offset)))->subRows.last;
return row;
}
