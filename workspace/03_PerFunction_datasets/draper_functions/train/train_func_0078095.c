__ecereMethod___ecereNameSpace__ecere__gfx__drivers__XDisplayDriver_SetBackground(struct __ecereNameSpace__ecere__com__Instance * display, struct __ecereNameSpace__ecere__com__Instance * surface, unsigned int color)
{
struct __ecereNameSpace__ecere__gfx__drivers__XSurface * xSurface = ((struct __ecereNameSpace__ecere__gfx__Surface *)(((char *)surface + __ecereClass___ecereNameSpace__ecere__gfx__Surface->offset)))->driverData;
struct __ecereNameSpace__ecere__gfx__drivers__XDisplay * xDisplay = ((struct __ecereNameSpace__ecere__gfx__Display *)(((char *)display + __ecereClass___ecereNameSpace__ecere__gfx__Display->offset)))->driverData;

xSurface->background = color;
XSetBackground(__ecereNameSpace__ecere__gui__drivers__xGlobalDisplay, xDisplay->gc, (__ecereNameSpace__ecere__gui__drivers__xSystemPixelFormat == 5) ? (unsigned int)xSurface->background : ((__ecereNameSpace__ecere__gui__drivers__xSystemPixelFormat == 4) ? ((unsigned short)(unsigned short)__ecereProp___ecereNameSpace__ecere__gfx__Color565_Set___ecereNameSpace__ecere__gfx__Color(__ecereProp___ecereNameSpace__ecere__gfx__ColorAlpha_Get___ecereNameSpace__ecere__gfx__Color(xSurface->background))) : ((unsigned short)(unsigned short)__ecereProp___ecereNameSpace__ecere__gfx__Color555_Set___ecereNameSpace__ecere__gfx__Color(__ecereProp___ecereNameSpace__ecere__gfx__ColorAlpha_Get___ecereNameSpace__ecere__gfx__Color(xSurface->background)))));
}
