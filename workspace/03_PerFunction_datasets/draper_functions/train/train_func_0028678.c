__ecereMethod___ecereNameSpace__ecere__gui__FormDesigner_OnLeftDoubleClick(struct __ecereNameSpace__ecere__com__Instance * this, int x, int y, unsigned int mods)
{
struct __ecereNameSpace__ecere__gui__FormDesigner * __ecerePointer___ecereNameSpace__ecere__gui__FormDesigner = (struct __ecereNameSpace__ecere__gui__FormDesigner *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__FormDesigner->offset) : 0);
struct __ecereNameSpace__ecere__com__Instance * control = __ecereNameSpace__ecere__gui__FindWindow(__ecerePointer___ecereNameSpace__ecere__gui__FormDesigner->form, __ecereNameSpace__ecere__com__activeDesigner, (((void *)0)), x, y, 0x0, &x, &y);

if(control && __ecerePointer___ecereNameSpace__ecere__gui__FormDesigner->selected == control)
{
((void (*)(struct __ecereNameSpace__ecere__com__Instance *, struct __ecereNameSpace__ecere__com__Instance * instance, struct __ecereNameSpace__ecere__com__Instance * classInstance))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = __ecereNameSpace__ecere__com__activeDesigner;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__com__DesignerBase->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__com__DesignerBase_AddDefaultMethod])(__ecereNameSpace__ecere__com__activeDesigner, control, __ecerePointer___ecereNameSpace__ecere__gui__FormDesigner->form);
return 0x0;
}
return 0x1;
}
