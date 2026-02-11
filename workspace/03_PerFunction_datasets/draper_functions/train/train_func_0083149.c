__ecereMethod_IDEWorkSpace_ValgrindLCSelect(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * selection, unsigned int mods)
{
struct IDEWorkSpace * __ecerePointer_IDEWorkSpace = (struct IDEWorkSpace *)(this ? (((char *)this) + __ecereClass_IDEWorkSpace->offset) : 0);

if(__ecereProp_IDEWorkSpace_Get_workspace(((struct IDEMainFrame *)(((char *)ideMainFrame + __ecereClass_IDEMainFrame->offset)))->ideWorkSpace))
{
if(__ecereProp___ecereNameSpace__ecere__gui__controls__MenuItem_Get_checked(selection))
{
int vgLeakCheck = (int)__ecereProp___ecereNameSpace__ecere__gui__controls__MenuItem_Get_id(selection);

__ecereProp___ecereNameSpace__ecere__gui__controls__MenuItem_Set_checked(__ecerePointer_IDEWorkSpace->debugValgrindNoLeakCheckItem, __ecereProp___ecereNameSpace__ecere__gui__controls__MenuItem_Get_id(__ecerePointer_IDEWorkSpace->debugValgrindNoLeakCheckItem) == vgLeakCheck);
__ecereProp___ecereNameSpace__ecere__gui__controls__MenuItem_Set_checked(__ecerePointer_IDEWorkSpace->debugValgrindSummaryLeakCheckItem, __ecereProp___ecereNameSpace__ecere__gui__controls__MenuItem_Get_id(__ecerePointer_IDEWorkSpace->debugValgrindSummaryLeakCheckItem) == vgLeakCheck);
__ecereProp___ecereNameSpace__ecere__gui__controls__MenuItem_Set_checked(__ecerePointer_IDEWorkSpace->debugValgrindYesLeakCheckItem, __ecereProp___ecereNameSpace__ecere__gui__controls__MenuItem_Get_id(__ecerePointer_IDEWorkSpace->debugValgrindYesLeakCheckItem) == vgLeakCheck);
__ecereProp___ecereNameSpace__ecere__gui__controls__MenuItem_Set_checked(__ecerePointer_IDEWorkSpace->debugValgrindFullLeakCheckItem, __ecereProp___ecereNameSpace__ecere__gui__controls__MenuItem_Get_id(__ecerePointer_IDEWorkSpace->debugValgrindFullLeakCheckItem) == vgLeakCheck);
__extension__ ({
char * __ecTemp1 = (__ecereProp_IDEWorkSpace_Get_workspace(((struct IDEMainFrame *)(((char *)ideMainFrame + __ecereClass_IDEMainFrame->offset)))->ideWorkSpace));

((struct Workspace *)(__ecTemp1 + __ecereClass_Workspace->offset));
})->vgLeakCheck = vgLeakCheck;
__ecereMethod_Workspace_Save(__ecereProp_IDEWorkSpace_Get_workspace(((struct IDEMainFrame *)(((char *)ideMainFrame + __ecereClass_IDEMainFrame->offset)))->ideWorkSpace));
}
else
__ecereProp___ecereNameSpace__ecere__gui__controls__MenuItem_Set_checked(selection, 0x1);
}
return 0x1;
}
