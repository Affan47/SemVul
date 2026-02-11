__ecereMethod___ecereNameSpace__ecere__gui__GuiApplication_SetCurrentCursor(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * window, struct __ecereNameSpace__ecere__com__Instance * cursor)
{
struct __ecereNameSpace__ecere__gui__GuiApplication * __ecerePointer___ecereNameSpace__ecere__gui__GuiApplication = (struct __ecereNameSpace__ecere__gui__GuiApplication *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__GuiApplication->offset) : 0);

__ecerePointer___ecereNameSpace__ecere__gui__GuiApplication->currentCursor = cursor;
if(cursor)
{
if(__ecerePointer___ecereNameSpace__ecere__gui__GuiApplication->fullScreenMode && ((struct __ecereNameSpace__ecere__gui__Cursor *)(((char *)cursor + __ecereClass___ecereNameSpace__ecere__gui__Cursor->offset)))->bitmap)
((void (*)(struct __ecereNameSpace__ecere__com__Instance * window, int cursor))__ecerePointer___ecereNameSpace__ecere__gui__GuiApplication->interfaceDriver->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__gui__Interface_SetMouseCursor])(window ? window : __ecerePointer___ecereNameSpace__ecere__gui__GuiApplication->desktop, (int)-1);
else
{
((void (*)(struct __ecereNameSpace__ecere__com__Instance * window, int cursor))__ecerePointer___ecereNameSpace__ecere__gui__GuiApplication->interfaceDriver->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__gui__Interface_SetMouseCursor])(window ? window : __ecerePointer___ecereNameSpace__ecere__gui__GuiApplication->desktop, ((struct __ecereNameSpace__ecere__gui__Cursor *)(((char *)cursor + __ecereClass___ecereNameSpace__ecere__gui__Cursor->offset)))->systemCursor);
__ecereMethod___ecereNameSpace__ecere__gfx__Bitmap_Free(__ecerePointer___ecereNameSpace__ecere__gui__GuiApplication->cursorBackground);
}
}
__ecerePointer___ecereNameSpace__ecere__gui__GuiApplication->cursorUpdate = 0x1;
}
