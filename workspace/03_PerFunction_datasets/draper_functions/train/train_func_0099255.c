__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_GoToPosition(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__gui__controls__EditLine * line, int y, int x)
{
struct __ecereNameSpace__ecere__gui__controls__EditBox * __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox = (struct __ecereNameSpace__ecere__gui__controls__EditBox *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__EditBox->offset) : 0);

if(!line)
{
int c;

for(line = __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->lines.first, c = 0; c < y && line; c++, line = __ecereProp___ecereNameSpace__ecere__gui__controls__EditLine_Get_next(line))
;
}
if(line)
{
if(__ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->y != y)
__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_DirtyAll(this);
else
__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_DirtyLine(this, y);
__ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->x = x;
__ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->y = y;
__ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->line = line;
__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_ComputeColumn(this);
__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox__Deselect(this);
__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_SetViewToCursor(this, 0x1);
return 0x1;
}
return 0x0;
}
