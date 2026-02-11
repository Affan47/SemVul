__ecereInstMeth_OutputView_OnCodeLocationParseAndGoTo__00000006(struct __ecereNameSpace__ecere__com__Instance * this, char * line)
{
struct OutputView * __ecerePointer_OutputView = (struct OutputView *)(this ? (((char *)this) + __ecereClass_OutputView->offset) : 0);

__ecereMethod_IDEWorkSpace_CodeLocationParseAndGoTo(((struct IDEMainFrame *)(((char *)ideMainFrame + __ecereClass_IDEMainFrame->offset)))->ideWorkSpace, line, __ecereProp_FindInFilesDialog_Get_findProject(((struct IDEWorkSpace *)(((char *)((struct IDEMainFrame *)(((char *)ideMainFrame + __ecereClass_IDEMainFrame->offset)))->ideWorkSpace + __ecereClass_IDEWorkSpace->offset)))->findInFilesDialog), __ecereProp_FindInFilesDialog_Get_findDir(((struct IDEWorkSpace *)(((char *)((struct IDEMainFrame *)(((char *)ideMainFrame + __ecereClass_IDEMainFrame->offset)))->ideWorkSpace + __ecereClass_IDEWorkSpace->offset)))->findInFilesDialog));
}
