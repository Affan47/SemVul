__ecereMethod_Debugger_GdbExecAdvance(struct __ecereNameSpace__ecere__com__Instance * this, char * absoluteFilePathOrLocation, int lineNumber)
{
struct Debugger * __ecerePointer_Debugger = (struct Debugger *)(this ? (((char *)this) + __ecereClass_Debugger->offset) : 0);
char relativeFilePath[797];

;
__ecerePointer_Debugger->gdbExecution = 5;
__ecereMethod_Debugger_GdbExecCommon(this);
if(lineNumber)
{
WorkspaceGetRelativePath(absoluteFilePathOrLocation, relativeFilePath, (((void *)0)));
__ecereMethod_Debugger_GdbCommand(0, 0x1, "advance %s:%d", relativeFilePath, lineNumber);
}
else
__ecereMethod_Debugger_GdbCommand(0, 0x1, "advance %s", absoluteFilePathOrLocation);
}
