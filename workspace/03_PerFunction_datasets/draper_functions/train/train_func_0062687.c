__ecereMethod_Sheet_ToggleSheet(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct Sheet * __ecerePointer_Sheet = (struct Sheet *)(this ? (((char *)this) + __ecereClass_Sheet->offset) : 0);

if(!__ecereProp___ecereNameSpace__ecere__gui__controls__Button_Get_checked(__ecerePointer_Sheet->propBtn))
{
__ecereProp___ecereNameSpace__ecere__gui__controls__Button_Set_checked(__ecerePointer_Sheet->propBtn, 0x1);
((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, struct __ecereNameSpace__ecere__com__Instance * button, int x, int y, unsigned int mods))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = __ecerePointer_Sheet->propBtn;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__gui__controls__Button->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__gui__controls__Button_NotifyClicked])(this, __ecerePointer_Sheet->propBtn, 0, 0, 0);
}
else
{
__ecereProp___ecereNameSpace__ecere__gui__controls__Button_Set_checked(__ecerePointer_Sheet->methBtn, 0x1);
((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, struct __ecereNameSpace__ecere__com__Instance * button, int x, int y, unsigned int mods))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = __ecerePointer_Sheet->methBtn;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__gui__controls__Button->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__gui__controls__Button_NotifyClicked])(this, __ecerePointer_Sheet->methBtn, 0, 0, 0);
}
}
