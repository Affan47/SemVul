__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_Save(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * f, unsigned int cr)
{
struct __ecereNameSpace__ecere__gui__controls__EditBox * __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox = (struct __ecereNameSpace__ecere__gui__controls__EditBox *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__EditBox->offset) : 0);
struct __ecereNameSpace__ecere__gui__controls__EditLine * line;

__ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->savedAction = ((struct __ecereNameSpace__ecere__gui__controls__UndoBuffer *)(((char *)__ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->undoBuffer + __ecereClass___ecereNameSpace__ecere__gui__controls__UndoBuffer->offset)))->curAction;
for(line = __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->lines.first; line; line = __ecereProp___ecereNameSpace__ecere__gui__controls__EditLine_Get_next(line))
{
if(((unsigned int)((__ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->style & 0x8000) >> 15)) && __ecereProp___ecereNameSpace__ecere__gui__controls__EditLine_Get_count(line) && isspace(line->buffer[__ecereProp___ecereNameSpace__ecere__gui__controls__EditLine_Get_count(line) - 1]))
{
int c = 0;

for(c = __ecereProp___ecereNameSpace__ecere__gui__controls__EditLine_Get_count(line) - 2; c >= -1; c--)
{
if(c == -1 || !isspace(line->buffer[c]))
{
c++;
line->buffer[c] = '\0';
line->count -= (__ecereProp___ecereNameSpace__ecere__gui__controls__EditLine_Get_count(line) - c);
break;
}
}
}
((int (*)(struct __ecereNameSpace__ecere__com__Instance *, void *  buffer, unsigned int size, unsigned int count))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = f;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__sys__File->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__sys__File_Write])(f, line->buffer, __ecereProp___ecereNameSpace__ecere__gui__controls__EditLine_Get_count(line), 1);
if(__ecereProp___ecereNameSpace__ecere__gui__controls__EditLine_Get_next(line))
{
if(cr)
((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, char ch))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = f;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__sys__File->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__sys__File_Putc])(f, '\r');
((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, char ch))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = f;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__sys__File->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__sys__File_Putc])(f, '\n');
}
}
}
