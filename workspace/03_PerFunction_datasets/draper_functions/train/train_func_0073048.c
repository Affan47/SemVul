__ecereInstMeth___ecereNameSpace__ecere__gui__Window_OnMouseMove__00000007(struct __ecereNameSpace__ecere__com__Instance * this, int x, int y, unsigned int mods)
{
struct __ecereNameSpace__ecere__gui__Window * __ecerePointer___ecereNameSpace__ecere__gui__Window = (struct __ecereNameSpace__ecere__gui__Window *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__Window->offset) : 0);

if(((unsigned int)((mods & 0x10) >> 4)) && !((unsigned int)((mods & 0x100) >> 8)))
__ecereMethod___ecereNameSpace__ecere__gui__controls__CalendarControl_FindDate(((struct __ecereNameSpace__ecere__com__Instance *)__ecerePointer___ecereNameSpace__ecere__gui__Window->master), x, y, 0x0, 0x0);
return 0x1;
}
