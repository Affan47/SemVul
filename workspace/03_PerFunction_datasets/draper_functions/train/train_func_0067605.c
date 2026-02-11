__ecereMethod___ecereNameSpace__ecere__gui__controls__TabControl_GetDecorationsSize(struct __ecereNameSpace__ecere__com__Instance * this, int * w, int * h)
{
struct __ecereNameSpace__ecere__gui__controls__TabControl * __ecerePointer___ecereNameSpace__ecere__gui__controls__TabControl = (struct __ecereNameSpace__ecere__gui__controls__TabControl *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__TabControl->offset) : 0);

if(__ecerePointer___ecereNameSpace__ecere__gui__controls__TabControl->placement == 1 && ((unsigned int)((((unsigned int)__ecereProp___ecereNameSpace__ecere__gui__Window_Get_borderStyle(this)) & 0x2) >> 1)))
{
*w = *h = 0;
if(((unsigned int)((((unsigned int)__ecereProp___ecereNameSpace__ecere__gui__Window_Get_borderStyle(this)) & 0x2) >> 1)) && (__ecereProp___ecereNameSpace__ecere__gui__Window_Get_state(this) != 2 || !__ecereProp___ecereNameSpace__ecere__gui__Window_Get_menuBar(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_parent(this))))
*h += 14;
if(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_hasMenuBar(this) && __ecereProp___ecereNameSpace__ecere__gui__Window_Get_state(this) != 1)
*h += 25;
if(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_statusBar(this) && __ecereProp___ecereNameSpace__ecere__gui__Window_Get_state(this) != 1)
*h += 18;
}
else
((void (*)(struct __ecereNameSpace__ecere__com__Instance *, int *  w, int *  h))__ecereClass___ecereNameSpace__ecere__gui__Window->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__gui__Window_GetDecorationsSize])(this, w, h);
}
