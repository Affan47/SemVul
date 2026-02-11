__ecereMethod_Debugger_GdbGetStack(struct __ecereNameSpace__ecere__com__Instance * this)
{
int __simpleStruct0;
struct Debugger * __ecerePointer_Debugger = (struct Debugger *)(this ? (((char *)this) + __ecereClass_Debugger->offset) : 0);

;
__ecerePointer_Debugger->activeFrame = (((void *)0));
__ecereMethod___ecereNameSpace__ecere__sys__OldList_Free(&__ecerePointer_Debugger->stackFrames, __ecereMethod_Frame_Free);
__ecereMethod_Debugger_GdbCommand(0, 0x0, "-stack-info-depth");
if(!__ecerePointer_Debugger->frameCount)
__ecereMethod_Debugger_GdbCommand(0, 0x0, "-stack-info-depth 192");
if(__ecerePointer_Debugger->frameCount && __ecerePointer_Debugger->frameCount <= 192)
__ecereMethod_Debugger_GdbCommand(0, 0x0, "-stack-list-frames 0 %d", (__simpleStruct0 = __ecerePointer_Debugger->frameCount - 1, (__simpleStruct0 < 191) ? __simpleStruct0 : 191));
else
{
int __simpleStruct1;
int __simpleStruct0;

__ecereMethod_Debugger_GdbCommand(0, 0x0, "-stack-list-frames 0 %d", (__simpleStruct0 = __ecerePointer_Debugger->frameCount - 1, (__simpleStruct0 < 95) ? __simpleStruct0 : 95));
__ecereMethod_Debugger_GdbCommand(0, 0x0, "-stack-list-frames %d %d", (__simpleStruct1 = __ecerePointer_Debugger->frameCount - 96, (__simpleStruct1 > 96) ? __simpleStruct1 : 96), __ecerePointer_Debugger->frameCount - 1);
}
__ecereMethod_Debugger_GdbCommand(0, 0x0, "");
}
