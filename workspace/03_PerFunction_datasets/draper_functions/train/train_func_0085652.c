__ecereInstMeth___ecereNameSpace__ecere__gui__controls__MenuItem_NotifySelect__00000029(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * selection, unsigned int mods)
{
struct IDEWorkSpace * __ecerePointer_IDEWorkSpace = (struct IDEWorkSpace *)(this ? (((char *)this) + __ecereClass_IDEWorkSpace->offset) : 0);

if(__ecerePointer_IDEWorkSpace->projectView)
{
if(!__ecereMethod_IDEWorkSpace_DontTerminateDebugSession(((struct IDEMainFrame *)(((char *)ideMainFrame + __ecereClass_IDEMainFrame->offset)))->ideWorkSpace, __ecereNameSpace__ecere__GetTranslatedString(__thisModule, "Project Close", (((void *)0)))))
__ecereMethod_IDEWorkSpace_ProjectClose(this);
}
return 0x1;
}
