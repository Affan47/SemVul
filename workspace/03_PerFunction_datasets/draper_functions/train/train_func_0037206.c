__ecereDestructor_Debugger(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct Debugger * __ecerePointer_Debugger = (struct Debugger *)(this ? (((char *)this) + __ecereClass_Debugger->offset) : 0);

{
;
((void (*)(struct __ecereNameSpace__ecere__com__Instance *))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = __ecerePointer_Debugger->sysBPs;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__com__List->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__com__Container_Free])(__ecerePointer_Debugger->sysBPs);
__ecereMethod_Debugger_Stop(this);
__ecereMethod_Debugger_CleanUp(this);
}
((__ecerePointer_Debugger->serialSemaphore ? (__ecereClass___ecereNameSpace__ecere__sys__Semaphore->Destructor ? __ecereClass___ecereNameSpace__ecere__sys__Semaphore->Destructor(__ecerePointer_Debugger->serialSemaphore) : 0, __ecereNameSpace__ecere__com__eSystem_Delete(__ecerePointer_Debugger->serialSemaphore)) : 0), __ecerePointer_Debugger->serialSemaphore = 0);
(__ecereNameSpace__ecere__com__eInstance_DecRef(__ecerePointer_Debugger->sysBPs), __ecerePointer_Debugger->sysBPs = 0);
(__ecereNameSpace__ecere__com__eInstance_DecRef(__ecerePointer_Debugger->vgLogThread), __ecerePointer_Debugger->vgLogThread = 0);
(__ecereNameSpace__ecere__com__eInstance_DecRef(__ecerePointer_Debugger->vgTargetThread), __ecerePointer_Debugger->vgTargetThread = 0);
(__ecereNameSpace__ecere__com__eInstance_DecRef(__ecerePointer_Debugger->gdbThread), __ecerePointer_Debugger->gdbThread = 0);
(__ecereNameSpace__ecere__com__eInstance_DecRef(__ecerePointer_Debugger->projectsLibraryLoaded), __ecerePointer_Debugger->projectsLibraryLoaded = 0);
(__ecereNameSpace__ecere__com__eInstance_DecRef(__ecerePointer_Debugger->gdbTimer), __ecerePointer_Debugger->gdbTimer = 0);
(__ecereNameSpace__ecere__com__eInstance_DecRef(__ecerePointer_Debugger->progThread), __ecerePointer_Debugger->progThread = 0);
}
