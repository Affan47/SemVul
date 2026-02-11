__ecereMethod___ecereNameSpace__ecere__gui__controls__StatusBar_AddField(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * field)
{
struct __ecereNameSpace__ecere__gui__controls__StatusBar * __ecerePointer___ecereNameSpace__ecere__gui__controls__StatusBar = (struct __ecereNameSpace__ecere__gui__controls__StatusBar *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__StatusBar->offset) : 0);

if(this && field)
{
((struct __ecereNameSpace__ecere__gui__controls__StatusField *)(((char *)field + __ecereClass___ecereNameSpace__ecere__gui__controls__StatusField->offset)))->_statusBar = this;
field->_refCount++;
__ecerePointer___ecereNameSpace__ecere__gui__controls__StatusBar->width += ((struct __ecereNameSpace__ecere__gui__controls__StatusField *)(((char *)field + __ecereClass___ecereNameSpace__ecere__gui__controls__StatusField->offset)))->width + (__ecereProp___ecereNameSpace__ecere__gui__GuiApplication_Get_textMode(__ecereNameSpace__ecere__gui__guiApp) ? 0 : 6);
__ecereMethod___ecereNameSpace__ecere__sys__OldList_Add(&__ecerePointer___ecereNameSpace__ecere__gui__controls__StatusBar->fields, field);
__ecereMethod___ecereNameSpace__ecere__gui__Window_Update(this, (((void *)0)));
}
}
