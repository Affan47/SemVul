__ecereMethod_ProjectView_ProjectRegenerate(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * selection, unsigned int mods)
{
struct ProjectView * __ecerePointer_ProjectView = (struct ProjectView *)(this ? (((char *)this) + __ecereClass_ProjectView->offset) : 0);
struct Project * prj = __ecerePointer_ProjectView->project;
struct __ecereNameSpace__ecere__com__Instance * compiler = __ecereMethod_IDESettings_GetCompilerConfig(ideSettings, __ecereProp_Workspace_Get_compiler(__ecereProp_IDEWorkSpace_Get_workspace(((struct IDEMainFrame *)(((char *)ideMainFrame + __ecereClass_IDEMainFrame->offset)))->ideWorkSpace)));

__ecereMethod_ProjectView_ShowOutputBuildLog(this, 0x1);
if(selection || !__ecereProp___ecereNameSpace__ecere__gui__Window_Get_activeClient(((struct IDEMainFrame *)(((char *)ideMainFrame + __ecereClass_IDEMainFrame->offset)))->ideWorkSpace))
{
struct __ecereNameSpace__ecere__com__Instance * row = __ecereProp___ecereNameSpace__ecere__gui__controls__ListBox_Get_currentRow(__ecerePointer_ProjectView->fileList);
struct ProjectNode * node = row ? (struct ProjectNode *)__ecereProp___ecereNameSpace__ecere__gui__controls__DataRow_Get_tag(row) : (((void *)0));

if(node)
prj = __ecereProp_ProjectNode_Get_project(node);
}
else
{
struct ProjectNode * node = __ecereMethod_ProjectView_GetNodeFromWindow(this, __ecereProp___ecereNameSpace__ecere__gui__Window_Get_activeClient(((struct IDEMainFrame *)(((char *)ideMainFrame + __ecereClass_IDEMainFrame->offset)))->ideWorkSpace), (((void *)0)), 0x1, 0x0, (((void *)0)));

if(node)
prj = __ecereProp_ProjectNode_Get_project(node);
}
__ecereMethod_ProjectView_DisplayCompiler(this, compiler, 0x0);
__ecereMethod_ProjectView_ProjectPrepareCompiler(this, __ecerePointer_ProjectView->project, compiler, 0x0);
__ecereMethod_ProjectView_ProjectPrepareMakefile(this, prj, 1, compiler, prj->config);
(__ecereNameSpace__ecere__com__eInstance_DecRef(compiler), compiler = 0);
return 0x1;
}
