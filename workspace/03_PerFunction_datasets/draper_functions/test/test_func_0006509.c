__ecereMethod_IDEWorkSpace_CreateProjectView(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * workspace, char * fileName)
{
struct __ecereNameSpace__ecere__com__Iterator __simpleStruct0;
struct IDEWorkSpace * __ecerePointer_IDEWorkSpace = (struct IDEWorkSpace *)(this ? (((char *)this) + __ecereClass_IDEWorkSpace->offset) : 0);
struct Project * project = ((struct Project *)__ecereProp___ecereNameSpace__ecere__com__Iterator_Get_data((__ecereProp___ecereNameSpace__ecere__com__Container_Get_firstIterator(((struct Workspace *)(((char *)workspace + __ecereClass_Workspace->offset)))->projects, &__simpleStruct0), &__simpleStruct0)));

__ecerePointer_IDEWorkSpace->projectView = __extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __ecereInstance1 = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass_ProjectView);

__ecereProp___ecereNameSpace__ecere__gui__Window_Set_parent(__ecereInstance1, this), __ecereProp___ecereNameSpace__ecere__gui__Window_Set_fileName(__ecereInstance1, fileName), __ecereNameSpace__ecere__com__eInstance_SetMethod(__ecereInstance1, "NotifyDestroyed", __ecereInstMeth_ProjectView_NotifyDestroyed__00000071), __ecereInstance1;
});
__ecereMethod___ecereNameSpace__ecere__gui__Window_Create(__ecerePointer_IDEWorkSpace->projectView);
__ecereMethod_IDEWorkSpace_RepositionWindows(this, 0x0);
__ecereProp_ProjectView_Set_workspace(__ecerePointer_IDEWorkSpace->projectView, workspace);
((struct ProjectView *)(((char *)__ecerePointer_IDEWorkSpace->projectView + __ecereClass_ProjectView->offset)))->project = project;
__ecereMethod___ecereNameSpace__ecere__gui__Window_SetText(ideMainFrame, "%s - %s", project->topNode->name, (__ecereNameSpace__ecere__GetTranslatedString(__thisModule, "Ecere IDE", (((void *)0)))));
__ecereMethod_IDEWorkSpace_AdjustMenus(this);
__ecereMethod_BreakpointsView_LoadFromWorkspace(((struct IDEWorkSpace *)(((char *)((struct IDEMainFrame *)(((char *)ideMainFrame + __ecereClass_IDEMainFrame->offset)))->ideWorkSpace + __ecereClass_IDEWorkSpace->offset)))->breakpointsView);
__ecereMethod_WatchesView_LoadFromWorkspace(((struct IDEWorkSpace *)(((char *)((struct IDEMainFrame *)(((char *)ideMainFrame + __ecereClass_IDEMainFrame->offset)))->ideWorkSpace + __ecereClass_IDEWorkSpace->offset)))->watchesView);
__ecereProp___ecereNameSpace__ecere__gui__controls__DataField_Set_userData(((struct FindInFilesDialog *)(((char *)__ecerePointer_IDEWorkSpace->findInFilesDialog + __ecereClass_FindInFilesDialog->offset)))->projectNodeField, __ecerePointer_IDEWorkSpace->projectView);
{
char fileName[797];

strcpy(fileName, project->topNode->path);
__ecereFunction___ecereNameSpace__ecere__sys__PathCat(fileName, project->topNode->name);
}
return __ecerePointer_IDEWorkSpace->projectView;
}
