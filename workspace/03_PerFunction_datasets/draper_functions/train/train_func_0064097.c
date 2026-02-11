__ecereMethod_IDEWorkSpace_OnClose(struct __ecereNameSpace__ecere__com__Instance * this, unsigned int parentClosing)
{
struct IDEWorkSpace * __ecerePointer_IDEWorkSpace = (struct IDEWorkSpace *)(this ? (((char *)this) + __ecereClass_IDEWorkSpace->offset) : 0);

if(__ecerePointer_IDEWorkSpace->projectView && __ecereProp_BuildState_Get_bool(((struct ProjectView *)(((char *)__ecerePointer_IDEWorkSpace->projectView + __ecereClass_ProjectView->offset)))->buildInProgress))
return 0x0;
if(__ecereMethod_IDEWorkSpace_DontTerminateDebugSession(this, __ecereNameSpace__ecere__GetTranslatedString(__thisModule, "Close IDE", (((void *)0)))))
return 0x0;
if(__ecerePointer_IDEWorkSpace->findInFilesDialog)
__ecereMethod_FindInFilesDialog_SearchStop(__ecerePointer_IDEWorkSpace->findInFilesDialog);
if(__ecereProp_IDEWorkSpace_Get_workspace(this))
{
__ecereMethod___ecereNameSpace__ecere__gui__Timer_Stop(__extension__ ({
char * __ecTemp1 = (__ecereProp_IDEWorkSpace_Get_workspace(this));

((struct Workspace *)(__ecTemp1 + __ecereClass_Workspace->offset));
})->timer);
__ecereMethod_Workspace_Save(__ecereProp_IDEWorkSpace_Get_workspace(this));
}
__ecereMethod___ecereNameSpace__ecere__gui__Window_Destroy(ideMainFrame, 0);
return 0x1;
}
