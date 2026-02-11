__ecereMethod___ecereNameSpace__ecere__gui__Timer_Stop(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__ecere__gui__Timer * __ecerePointer___ecereNameSpace__ecere__gui__Timer = (struct __ecereNameSpace__ecere__gui__Timer *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__Timer->offset) : 0);

if(__ecerePointer___ecereNameSpace__ecere__gui__Timer->started)
{
__ecerePointer___ecereNameSpace__ecere__gui__Timer->started = 0x0;
__ecereMethod___ecereNameSpace__ecere__sys__OldList_Remove(&((struct __ecereNameSpace__ecere__gui__GuiApplication *)(((char *)__ecereNameSpace__ecere__gui__guiApp + __ecereClass___ecereNameSpace__ecere__gui__GuiApplication->offset)))->windowTimers, this);
(__ecereNameSpace__ecere__com__eInstance_DecRef(this), this = 0);
}
}
