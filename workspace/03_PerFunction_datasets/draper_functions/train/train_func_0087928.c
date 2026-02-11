__ecereMethod___ecereNameSpace__ecere__gui__controls__Button_OnMouseLeave(struct __ecereNameSpace__ecere__com__Instance * this, unsigned int mods)
{
struct __ecereNameSpace__ecere__gui__controls__Button * __ecerePointer___ecereNameSpace__ecere__gui__controls__Button = (struct __ecereNameSpace__ecere__gui__controls__Button *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__Button->offset) : 0);

if(!__ecerePointer___ecereNameSpace__ecere__gui__controls__Button->key)
{
if((!((unsigned int)((__ecerePointer___ecereNameSpace__ecere__gui__controls__Button->buttonStyle & 0x8) >> 3)) || !__ecerePointer___ecereNameSpace__ecere__gui__controls__Button->hint))
{
if(!((unsigned int)((__ecerePointer___ecereNameSpace__ecere__gui__controls__Button->buttonStyle & 0x20) >> 5)) || __ecerePointer___ecereNameSpace__ecere__gui__controls__Button->state == 2)
__ecerePointer___ecereNameSpace__ecere__gui__controls__Button->state = 0;
}
if(((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, struct __ecereNameSpace__ecere__com__Instance * button, unsigned int mods))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = this;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__gui__controls__Button->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__gui__controls__Button_NotifyMouseLeave])(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_master(this), this, mods))
__ecereMethod___ecereNameSpace__ecere__gui__Window_Update(this, (((void *)0)));
}
__ecerePointer___ecereNameSpace__ecere__gui__controls__Button->over = 0x0;
return 0x1;
}
