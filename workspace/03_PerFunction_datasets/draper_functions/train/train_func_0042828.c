__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_Cut(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__ecere__gui__controls__EditBox * __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox = (struct __ecereNameSpace__ecere__gui__controls__EditBox *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__EditBox->offset) : 0);

if(this)
{
__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_Copy(this);
if(__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_DelSel(this, (((void *)0))))
{
__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_SetViewToCursor(this, 0x1);
__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_Modified(this);
}
}
}
