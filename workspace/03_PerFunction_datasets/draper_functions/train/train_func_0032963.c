__ecereInstMeth___ecereNameSpace__ecere__gui__controls__ListBox_NotifyDoubleClick__00000007(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * control, int x, int y, unsigned int mods)
{
struct __ecereNameSpace__ecere__gui__dialogs__FileDialog * __ecerePointer___ecereNameSpace__ecere__gui__dialogs__FileDialog = (struct __ecereNameSpace__ecere__gui__dialogs__FileDialog *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__dialogs__FileDialog->offset) : 0);
unsigned int result = 0x1;
char * selectedFileName = (((void *)0));

if(__ecereMethod___ecereNameSpace__ecere__gui__dialogs__FileDialog_GetNamesFromRow(this, __ecereProp___ecereNameSpace__ecere__gui__controls__ListBox_Get_currentRow(control), &selectedFileName))
{
result = __ecereMethod___ecereNameSpace__ecere__gui__dialogs__FileDialog_SelectFile(this, selectedFileName, 0, 0x0);
}
(__ecereNameSpace__ecere__com__eSystem_Delete(selectedFileName), selectedFileName = 0);
return result;
}
