GetLocText(struct __ecereNameSpace__ecere__com__Instance * editBox, struct __ecereNameSpace__ecere__com__Instance * f, int position, struct Location * loc, char ** text, int * size, int pad, int linePad)
{
struct __ecereNameSpace__ecere__gui__controls__EditLine * l1, * l2;
int y1, x1, y2, x2;

__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_GetSelPos(editBox, &l1, &y1, &x1, &l2, &y2, &x2, 0x0);
{
struct __ecereNameSpace__ecere__gui__controls__EditLine * l1, * l2;
int y1, x1, y2, x2;

((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, int pos, int mode))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = f;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__sys__File->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__sys__File_Seek])(f, loc->start.pos - position, 1);
l1 = __ecereProp___ecereNameSpace__ecere__gui__controls__EditBox_Get_line(editBox);
x1 = __ecereProp___ecereNameSpace__ecere__gui__controls__EditBox_Get_charPos(editBox);
y1 = __ecereProp___ecereNameSpace__ecere__gui__controls__EditBox_Get_lineNumber(editBox);
((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, int pos, int mode))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = f;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__sys__File->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__sys__File_Seek])(f, loc->end.pos - loc->start.pos, 1);
l2 = __ecereProp___ecereNameSpace__ecere__gui__controls__EditBox_Get_line(editBox);
x2 = __ecereProp___ecereNameSpace__ecere__gui__controls__EditBox_Get_charPos(editBox);
y2 = __ecereProp___ecereNameSpace__ecere__gui__controls__EditBox_Get_lineNumber(editBox);
__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_SetSelPos(editBox, l1, y1, x1, l2, y2, x2);
*size = __ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_SelSize(editBox);
*text = __ecereNameSpace__ecere__com__eSystem_New(sizeof(char) * (*size + 1 + (y2 - y1 + 1) * linePad + pad));
__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_GetSel(editBox, *text, 0x0);
}
__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_SetSelPos(editBox, l1, y1, x1, l2, y2, x2);
__ecereMethod___ecereNameSpace__ecere__sys__File_Printf(f, "");
}
