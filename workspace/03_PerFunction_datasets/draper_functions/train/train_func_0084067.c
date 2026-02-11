__ecereProp___ecereNameSpace__ecere__gui__dialogs__ReplaceDialog_Set_editBox(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * value)
{
struct __ecereNameSpace__ecere__gui__dialogs__ReplaceDialog * __ecerePointer___ecereNameSpace__ecere__gui__dialogs__ReplaceDialog = (struct __ecereNameSpace__ecere__gui__dialogs__ReplaceDialog *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__dialogs__ReplaceDialog->offset) : 0);
int x1, y1, x2, y2;

__ecerePointer___ecereNameSpace__ecere__gui__dialogs__ReplaceDialog->editBox = value;
if(value)
__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_GetSelPos(value, (((void *)0)), &y1, &x1, (((void *)0)), &y2, &x2, 0x1);
if(!__ecerePointer___ecereNameSpace__ecere__gui__dialogs__ReplaceDialog->editBox || (x1 == x2 && y1 == y2))
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_disabled(__ecerePointer___ecereNameSpace__ecere__gui__dialogs__ReplaceDialog->selection, 0x1);
if(y1 == y2 || !__ecerePointer___ecereNameSpace__ecere__gui__dialogs__ReplaceDialog->editBox)
__ecereProp___ecereNameSpace__ecere__gui__controls__Button_Set_checked(__ecerePointer___ecereNameSpace__ecere__gui__dialogs__ReplaceDialog->wholeFile, 0x1);
else
__ecereProp___ecereNameSpace__ecere__gui__controls__Button_Set_checked(__ecerePointer___ecereNameSpace__ecere__gui__dialogs__ReplaceDialog->selection, 0x1);
if(value && y1 == y2 && x1 != x2)
{
char * selection = __ecereNameSpace__ecere__com__eSystem_New(sizeof(char) * (__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_SelSize(value) + 1));

__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_GetSel(value, selection, 0x0);
__ecereProp___ecereNameSpace__ecere__gui__controls__EditBox_Set_contents(__ecerePointer___ecereNameSpace__ecere__gui__dialogs__ReplaceDialog->findWhat, selection);
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_disabled(__ecerePointer___ecereNameSpace__ecere__gui__dialogs__ReplaceDialog->findNext, !selection[0]);
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_disabled(__ecerePointer___ecereNameSpace__ecere__gui__dialogs__ReplaceDialog->replace, !selection[0]);
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_disabled(__ecerePointer___ecereNameSpace__ecere__gui__dialogs__ReplaceDialog->replaceAll, !selection[0]);
(__ecereNameSpace__ecere__com__eSystem_Delete(selection), selection = 0);
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_isDefault(__ecerePointer___ecereNameSpace__ecere__gui__dialogs__ReplaceDialog->replace, 0x1);
}
__ecereNameSpace__ecere__com__eInstance_FireSelfWatchers(this, __ecereProp___ecereNameSpace__ecere__gui__dialogs__ReplaceDialog_editBox), __ecereNameSpace__ecere__com__eInstance_FireSelfWatchers(this, __ecerePropM___ecereNameSpace__ecere__gui__dialogs__ReplaceDialog_editBox);
}
