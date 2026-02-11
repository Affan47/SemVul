__ecereInstMeth___ecereNameSpace__ecere__gui__controls__EditBox_NotifyDoubleClick__00000000(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * editBox, struct __ecereNameSpace__ecere__gui__controls__EditLine * line, unsigned int mods)
{
struct ThreadsView * __ecerePointer_ThreadsView = (struct ThreadsView *)(this ? (((char *)this) + __ecereClass_ThreadsView->offset) : 0);
int id = __ecereMethod_ThreadsView_GetThreadId(this);

((void (*)(struct __ecereNameSpace__ecere__com__Instance *, int threadId))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = this;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass_ThreadsView->_vTbl;
})[__ecereVMethodID_ThreadsView_OnSelectThread])(this, id);
return 0x1;
}
