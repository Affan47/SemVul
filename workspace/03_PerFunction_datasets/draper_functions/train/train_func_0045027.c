__ecereMethod___ecereNameSpace__ecere__gui__controls__PopupMenu_OnMouseMove(struct __ecereNameSpace__ecere__com__Instance * this, int mx, int my, unsigned int mods)
{
struct __ecereNameSpace__ecere__gui__controls__PopupMenu * __ecerePointer___ecereNameSpace__ecere__gui__controls__PopupMenu = (struct __ecereNameSpace__ecere__gui__controls__PopupMenu *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__PopupMenu->offset) : 0);
int selectedX, selectedY;
struct __ecereNameSpace__ecere__gui__controls__ItemPtr * selected;

if(((unsigned int)((mods & 0x100) >> 8)))
return 0x1;
selected = __ecereMethod___ecereNameSpace__ecere__gui__controls__PopupMenu_FindSelected(this, mx, my, &selectedX, &selectedY);
if((!((unsigned int)((mods & 0x100) >> 8)) || !__ecerePointer___ecereNameSpace__ecere__gui__controls__PopupMenu->selected) && (selected != __ecerePointer___ecereNameSpace__ecere__gui__controls__PopupMenu->selected && (!selected || !(((struct __ecereNameSpace__ecere__gui__controls__MenuItem *)(((char *)selected->item + __ecereClass___ecereNameSpace__ecere__gui__controls__MenuItem->offset)))->disabled || (((struct __ecereNameSpace__ecere__gui__controls__MenuItem *)(((char *)selected->item + __ecereClass___ecereNameSpace__ecere__gui__controls__MenuItem->offset)))->subMenu && !((struct __ecereNameSpace__ecere__gui__controls__Menu *)(((char *)((struct __ecereNameSpace__ecere__gui__controls__MenuItem *)(((char *)selected->item + __ecereClass___ecereNameSpace__ecere__gui__controls__MenuItem->offset)))->subMenu + __ecereClass___ecereNameSpace__ecere__gui__controls__Menu->offset)))->items.count))) && (selected || !__ecerePointer___ecereNameSpace__ecere__gui__controls__PopupMenu->keyboardFocus)))
{
if(!__ecerePointer___ecereNameSpace__ecere__gui__controls__PopupMenu->isMenuBar || __ecerePointer___ecereNameSpace__ecere__gui__controls__PopupMenu->pressed)
{
unsigned int pressed = __ecerePointer___ecereNameSpace__ecere__gui__controls__PopupMenu->pressed;

if(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_firstSlave(this))
__ecereMethod___ecereNameSpace__ecere__gui__Window_Destroy(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_firstSlave(this), 0);
__ecerePointer___ecereNameSpace__ecere__gui__controls__PopupMenu->selected = selected;
if(__ecerePointer___ecereNameSpace__ecere__gui__controls__PopupMenu->selected)
{
struct __ecereNameSpace__ecere__sys__Point __simpleStruct0;
struct __ecereNameSpace__ecere__com__Instance * childMenu = ((struct __ecereNameSpace__ecere__gui__controls__MenuItem *)(((char *)selected->item + __ecereClass___ecereNameSpace__ecere__gui__controls__MenuItem->offset)))->subMenu;

__ecerePointer___ecereNameSpace__ecere__gui__controls__PopupMenu->pressed = pressed;
if(((struct __ecereNameSpace__ecere__gui__controls__MenuItem *)(((char *)__ecerePointer___ecereNameSpace__ecere__gui__controls__PopupMenu->selected->item + __ecereClass___ecereNameSpace__ecere__gui__controls__MenuItem->offset)))->subMenu)
__ecereMethod___ecereNameSpace__ecere__gui__controls__PopupMenu_MenuPopupChild(this, selectedX, (__ecereProp___ecereNameSpace__ecere__gui__Window_Get_position(this, &__simpleStruct0), __simpleStruct0.y + selectedY), childMenu);
if(pressed)
__ecerePointer___ecereNameSpace__ecere__gui__controls__PopupMenu->keyboardFocus = 0x1;
}
}
else
__ecerePointer___ecereNameSpace__ecere__gui__controls__PopupMenu->selected = selected;
__ecereMethod___ecereNameSpace__ecere__gui__Window_Update(this, (((void *)0)));
}
return 0x1;
}
