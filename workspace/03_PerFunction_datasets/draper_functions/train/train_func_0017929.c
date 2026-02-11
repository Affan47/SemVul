__ecereMethod___ecereNameSpace__ecere__gui__FormDesigner_Reset(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__ecere__gui__FormDesigner * __ecerePointer___ecereNameSpace__ecere__gui__FormDesigner = (struct __ecereNameSpace__ecere__gui__FormDesigner *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__FormDesigner->offset) : 0);

__ecerePointer___ecereNameSpace__ecere__gui__FormDesigner->form = (((void *)0));
__ecereMethod___ecereNameSpace__ecere__gui__Window_FreeMouseRange();
__ecerePointer___ecereNameSpace__ecere__gui__FormDesigner->moved = (((void *)0));
__ecerePointer___ecereNameSpace__ecere__gui__FormDesigner->selected = (((void *)0));
}
