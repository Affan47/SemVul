__ecereMethod___ecereNameSpace__ecere__gui__controls__ScrollBar_OnMouseLeave(struct __ecereNameSpace__ecere__com__Instance * this, unsigned int mods)
{
struct __ecereNameSpace__ecere__gui__controls__ScrollBar * __ecerePointer___ecereNameSpace__ecere__gui__controls__ScrollBar = (struct __ecereNameSpace__ecere__gui__controls__ScrollBar *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__ScrollBar->offset) : 0);

__ecerePointer___ecereNameSpace__ecere__gui__controls__ScrollBar->inside = 0x0;
if(__ecerePointer___ecereNameSpace__ecere__gui__controls__ScrollBar->action == 3 || __ecerePointer___ecereNameSpace__ecere__gui__controls__ScrollBar->action == 4)
__ecereMethod___ecereNameSpace__ecere__gui__Window_Update(this, (((void *)0)));
return 0x1;
}
