__ecereMethod___ecereNameSpace__ecere__gui__controls__ListBox_GetCell(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance ** row, struct __ecereNameSpace__ecere__com__Instance ** field)
{
struct __ecereNameSpace__ecere__gui__controls__ListBox * __ecerePointer___ecereNameSpace__ecere__gui__controls__ListBox = (struct __ecereNameSpace__ecere__gui__controls__ListBox *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__ListBox->offset) : 0);
struct __ecereNameSpace__ecere__gui__controls__ListBoxCell * cell = (((void *)0));

if(!*row)
*row = __ecerePointer___ecereNameSpace__ecere__gui__controls__ListBox->currentRow;
if(*row)
{
if(!*field)
*field = this ? __ecerePointer___ecereNameSpace__ecere__gui__controls__ListBox->currentField : (((void *)0));
if(!*field && this)
{
for(*field = __ecerePointer___ecereNameSpace__ecere__gui__controls__ListBox->fields.first; __ecereProp___ecereNameSpace__ecere__gui__controls__DataField_Get_index((*field)) != 0; *field = __ecereProp___ecereNameSpace__ecere__gui__controls__DataField_Get_next((*field)))
;
}
if(*field)
{
unsigned int index;

if(__extension__ ({
char * __ecTemp1 = ((*field));

((struct __ecereNameSpace__ecere__gui__controls__DataField *)(__ecTemp1 + __ecereClass___ecereNameSpace__ecere__gui__controls__DataField->offset));
})->listBox == this)
{
for(index = 0, cell = __extension__ ({
char * __ecTemp1 = ((*row));

((struct __ecereNameSpace__ecere__gui__controls__DataRow *)(__ecTemp1 + __ecereClass___ecereNameSpace__ecere__gui__controls__DataRow->offset));
})->cells.first; cell && index != __ecereProp___ecereNameSpace__ecere__gui__controls__DataField_Get_index((*field)); index++, cell = cell->next)
;
}
}
}
return cell;
}
