__ecereMethod___ecereNameSpace__ecere__gui__controls__DropBox_Clear(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__ecere__gui__controls__DropBox * __ecerePointer___ecereNameSpace__ecere__gui__controls__DropBox = (struct __ecereNameSpace__ecere__gui__controls__DropBox *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__DropBox->offset) : 0);

if(this)
{
struct __ecereNameSpace__ecere__com__Instance * master = __ecereProp___ecereNameSpace__ecere__gui__Window_Get_master(this);

__ecereMethod___ecereNameSpace__ecere__gui__controls__ListBox_Clear(__ecerePointer___ecereNameSpace__ecere__gui__controls__DropBox->listBox);
if(__ecerePointer___ecereNameSpace__ecere__gui__controls__DropBox->currentRow && master)
{
__ecerePointer___ecereNameSpace__ecere__gui__controls__DropBox->currentRow = (((void *)0));
((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, struct __ecereNameSpace__ecere__com__Instance * dropBox, struct __ecereNameSpace__ecere__com__Instance * row, unsigned int mods))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = this;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__gui__controls__DropBox->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__gui__controls__DropBox_NotifySelect])(master, this, (((void *)0)), 0);
}
__ecerePointer___ecereNameSpace__ecere__gui__controls__DropBox->currentRow = (((void *)0));
if(((unsigned int)((__ecerePointer___ecereNameSpace__ecere__gui__controls__DropBox->style & 0x4) >> 2)) && ((unsigned int)((__ecerePointer___ecereNameSpace__ecere__gui__controls__DropBox->style & 0x20) >> 5)))
__ecereProp___ecereNameSpace__ecere__gui__controls__EditBox_Set_contents(__ecerePointer___ecereNameSpace__ecere__gui__controls__DropBox->editBox, "");
__ecereMethod___ecereNameSpace__ecere__gui__Window_Update(this, (((void *)0)));
if(((unsigned int)((__ecerePointer___ecereNameSpace__ecere__gui__controls__DropBox->style & 0x10) >> 4)))
__ecerePointer___ecereNameSpace__ecere__gui__controls__DropBox->noneRow = __ecereMethod___ecereNameSpace__ecere__gui__controls__ListBox_AddRowNone(__ecerePointer___ecereNameSpace__ecere__gui__controls__DropBox->listBox);
}
}
