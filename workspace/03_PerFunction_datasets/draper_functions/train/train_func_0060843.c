__ecereInstMeth___ecereNameSpace__ecere__gui__controls__MenuItem_NotifySelect__00000019(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * selection, unsigned int mods)
{
struct IDEWorkSpace * __ecerePointer_IDEWorkSpace = (struct IDEWorkSpace *)(this ? (((char *)this) + __ecereClass_IDEWorkSpace->offset) : 0);

if(!__ecerePointer_IDEWorkSpace->projectView && __ecereProp_IDESettings_Get_ideFileDialogLocation(ideSettings))
__ecereProp___ecereNameSpace__ecere__gui__dialogs__FileDialog_Set_currentDirectory(ideFileDialog, __ecereProp_IDESettings_Get_ideFileDialogLocation(ideSettings));
for(; ; )
{
if(__ecereMethod___ecereNameSpace__ecere__gui__Window_Modal(ideFileDialog) == 0x3)
{
unsigned int gotWhatWeWant = 0x0;
int c;
int numSelections = __ecereProp___ecereNameSpace__ecere__gui__dialogs__FileDialog_Get_numSelections(ideFileDialog);
char ** multiFilePaths = __ecereProp___ecereNameSpace__ecere__gui__dialogs__FileDialog_Get_multiFilePaths(ideFileDialog);

for(c = 0; c < numSelections; c++)
{
if(__ecereMethod_IDEWorkSpace_OpenFile(this, multiFilePaths[c], 0, 0x1, ((struct __ecereNameSpace__ecere__gui__dialogs__FileType *)((struct __ecereNameSpace__ecere__com__Array *)(((char *)fileTypes + 24)))->array)[__ecereProp___ecereNameSpace__ecere__gui__dialogs__FileDialog_Get_fileType(ideFileDialog)].typeExtension, 0, 0, ((unsigned int)((mods & 0x2) >> 1)) && ((unsigned int)((mods & 0x1) >> 0))))
gotWhatWeWant = 0x1;
}
if(gotWhatWeWant || __ecereMethod___ecereNameSpace__ecere__gui__Window_Modal(__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __ecereInstance1 = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass___ecereNameSpace__ecere__gui__dialogs__MessageBox);

__ecereProp___ecereNameSpace__ecere__gui__dialogs__MessageBox_Set_type(__ecereInstance1, 1), __ecereProp___ecereNameSpace__ecere__gui__Window_Set_master(__ecereInstance1, this), __ecereProp___ecereNameSpace__ecere__gui__Window_Set_text(__ecereInstance1, __ecereNameSpace__ecere__GetTranslatedString(__thisModule, "Error opening file", (((void *)0)))), __ecereProp___ecereNameSpace__ecere__gui__dialogs__MessageBox_Set_contents(__ecereInstance1, __ecereNameSpace__ecere__GetTranslatedString(__thisModule, "Open a different file?", (((void *)0)))), __ecereInstance1;
})) == 0x2)
{
if(!__ecerePointer_IDEWorkSpace->projectView && gotWhatWeWant)
__ecereMethod_IDEWorkSpace_ChangeFileDialogsDirectory(this, __ecereProp___ecereNameSpace__ecere__gui__dialogs__FileDialog_Get_currentDirectory(ideFileDialog), 0x1);
__ecereMethod_IDEWorkSpace_RepositionWindows(((struct IDEMainFrame *)(((char *)ideMainFrame + __ecereClass_IDEMainFrame->offset)))->ideWorkSpace, 0x0);
break;
}
}
else
break;
}
return 0x1;
}
