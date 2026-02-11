__ecereMethod_ProjectView_ProjectPrepareCompiler(struct __ecereNameSpace__ecere__com__Instance * this, struct Project * project, struct __ecereNameSpace__ecere__com__Instance * compiler, unsigned int silent)
{
struct ProjectView * __ecerePointer_ProjectView = (struct ProjectView *)(this ? (((char *)this) + __ecereClass_ProjectView->offset) : 0);

if((!__ecereMethod_Project_GenerateCrossPlatformMk(project, ((struct IDEApp *)(((char *)(((struct __ecereNameSpace__ecere__com__Instance *)__thisModule)) + __ecereClass_IDEApp->offset)))->includeFile) || !__ecereMethod_Project_GenerateCompilerCf(project, compiler, __ecereMethod_ProjectNode_ContainsFilesWithExtension(project->topNode, "ec", project->config))) && !silent)
__ecereMethod_LogBox_Logf(((struct OutputView *)(((char *)((struct IDEWorkSpace *)(((char *)((struct IDEMainFrame *)(((char *)ideMainFrame + __ecereClass_IDEMainFrame->offset)))->ideWorkSpace + __ecereClass_IDEWorkSpace->offset)))->outputView + __ecereClass_OutputView->offset)))->buildBox, __ecereNameSpace__ecere__GetTranslatedString(__thisModule, "Error generating compiler configuration (Is the project/config directory writable?)\n", (((void *)0))));
return 0x1;
}
