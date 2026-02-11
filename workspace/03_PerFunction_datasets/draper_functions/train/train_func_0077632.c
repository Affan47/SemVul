__ecereMethod___ecereNameSpace__ecere__gui__AnchorButton_OnRedraw(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * surface)
{
struct __ecereNameSpace__ecere__sys__Size __simpleStruct1;
struct __ecereNameSpace__ecere__sys__Size __simpleStruct0;
int cw = (int)(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_clientSize(this, &__simpleStruct0), __simpleStruct0).w;
int ch = (int)(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_clientSize(this, &__simpleStruct1), __simpleStruct1).h;

__ecereMethod___ecereNameSpace__ecere__gfx__Surface_SetForeground(surface, __ecereProp___ecereNameSpace__ecere__gfx__ColorAlpha_Set___ecereNameSpace__ecere__gfx__Color(0x0));
if(__ecereProp___ecereNameSpace__ecere__gui__controls__Button_Get_checked(this))
{
__ecereMethod___ecereNameSpace__ecere__gfx__Surface_SetBackground(surface, __ecereProp___ecereNameSpace__ecere__gfx__ColorAlpha_Set___ecereNameSpace__ecere__gfx__Color(0x555555));
__ecereMethod___ecereNameSpace__ecere__gfx__Surface_Area(surface, 0, 0, cw - 1, ch - 1);
}
else
__ecereMethod___ecereNameSpace__ecere__gfx__Surface_LineStipple(surface, 0xAAAA);
__ecereMethod___ecereNameSpace__ecere__gfx__Surface_Rectangle(surface, 0, 0, cw - 1, ch - 1);
if(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_active(this))
{
__ecereMethod___ecereNameSpace__ecere__gfx__Surface_LineStipple(surface, 0xAAAA);
__ecereMethod___ecereNameSpace__ecere__gfx__Surface_Rectangle(surface, 2, 2, cw - 3, ch - 3);
}
}
