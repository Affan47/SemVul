__ecereMethod_CodeEditor_OnSaveFile(struct __ecereNameSpace__ecere__com__Instance * this, char * fileName)
{
struct CodeEditor * __ecerePointer_CodeEditor = (struct CodeEditor *)(this ? (((char *)this) + __ecereClass_CodeEditor->offset) : 0);
struct __ecereNameSpace__ecere__com__Instance * f;

if(__ecerePointer_CodeEditor->designer)
{
__ecereMethod_CodeEditor_UpdateFormCode(this);
}
f = __ecereFunction___ecereNameSpace__ecere__sys__FileOpen(fileName, 2);
if(f)
{
if(!((struct IDEWorkSpace *)(((char *)((struct IDEMainFrame *)(((char *)ideMainFrame + __ecereClass_IDEMainFrame->offset)))->ideWorkSpace + __ecereClass_IDEWorkSpace->offset)))->projectView)
__ecereMethod_IDEWorkSpace_ChangeFileDialogsDirectory(((struct IDEMainFrame *)(((char *)ideMainFrame + __ecereClass_IDEMainFrame->offset)))->ideWorkSpace, __ecereProp___ecereNameSpace__ecere__gui__dialogs__FileDialog_Get_currentDirectory(codeEditorFileDialog), 0x1);
if(__ecerePointer_CodeEditor->designer)
{
if(!__ecereProp___ecereNameSpace__ecere__gui__Window_Get_fileName(this))
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_fileName(this, fileName);
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_fileName(__ecerePointer_CodeEditor->designer, fileName);
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_modifiedDocument(__ecerePointer_CodeEditor->designer, 0x0);
}
__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_Save(__ecerePointer_CodeEditor->editBox, f, 0x0);
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_modifiedDocument(this, 0x0);
(__ecereNameSpace__ecere__com__eInstance_DecRef(f), f = 0);
return 0x1;
}
return 0x0;
}
