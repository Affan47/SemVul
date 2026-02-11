__ecereMethod_BreakpointsView_RemoveBreakpoint(struct __ecereNameSpace__ecere__com__Instance * this, struct Breakpoint * bp)
{
struct BreakpointsView * __ecerePointer_BreakpointsView = (struct BreakpointsView *)(this ? (((char *)this) + __ecereClass_BreakpointsView->offset) : 0);

__ecereMethod___ecereNameSpace__ecere__gui__controls__ListBox_DeleteRow(__ecerePointer_BreakpointsView->listBox, bp->row);
bp->row = (((void *)0));
__ecereMethod___ecereNameSpace__ecere__gui__Window_Update(((struct IDEWorkSpace *)(((char *)((struct IDEMainFrame *)(((char *)ideMainFrame + __ecereClass_IDEMainFrame->offset)))->ideWorkSpace + __ecereClass_IDEWorkSpace->offset)))->callStackView, (((void *)0)));
__ecereMethod___ecereNameSpace__ecere__gui__Window_Update(this, (((void *)0)));
}
