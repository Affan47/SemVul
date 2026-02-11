__ecereMethod_Debugger_ValidateBreakpoint(struct __ecereNameSpace__ecere__com__Instance * this, struct Breakpoint * bp)
{
struct Debugger * __ecerePointer_Debugger = (struct Debugger *)(this ? (((char *)this) + __ecereClass_Debugger->offset) : 0);

;
if(__ecerePointer_Debugger->modules && bp->line && bp->bp)
{
if(bp->bp->line != bp->line)
{
if(!bp->bp->line)
{
return 0x0;
}
else
{
__ecereMethod_LogBox_Logf(((struct OutputView *)(((char *)((struct IDEWorkSpace *)(((char *)((struct IDEMainFrame *)(((char *)ideMainFrame + __ecereClass_IDEMainFrame->offset)))->ideWorkSpace + __ecereClass_IDEWorkSpace->offset)))->outputView + __ecereClass_OutputView->offset)))->debugBox, "Debugger Error: ValidateBreakpoint error\n");
bp->line = bp->bp->line;
}
}
}
return 0x1;
}
