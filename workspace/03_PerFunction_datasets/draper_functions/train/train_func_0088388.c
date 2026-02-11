__ecereMethod___ecereNameSpace__ecere__gui__controls__DataRow_GetNextRow(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__ecere__gui__controls__DataRow * __ecerePointer___ecereNameSpace__ecere__gui__controls__DataRow = (struct __ecereNameSpace__ecere__gui__controls__DataRow *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__DataRow->offset) : 0);
struct __ecereNameSpace__ecere__com__Instance * row;

if(__ecerePointer___ecereNameSpace__ecere__gui__controls__DataRow->subRows.first && !__ecerePointer___ecereNameSpace__ecere__gui__controls__DataRow->collapsed)
row = __ecerePointer___ecereNameSpace__ecere__gui__controls__DataRow->subRows.first;
else
{
for(row = this; row; row = __ecereProp___ecereNameSpace__ecere__gui__controls__DataRow_Get_parent(row))
{
if(__ecereProp___ecereNameSpace__ecere__gui__controls__DataRow_Get_next(row))
{
row = __ecereProp___ecereNameSpace__ecere__gui__controls__DataRow_Get_next(row);
break;
}
}
}
return row;
}
