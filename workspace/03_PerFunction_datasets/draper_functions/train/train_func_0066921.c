__ecereMethod___ecereNameSpace__ecere__gfx__drivers__OpenGLDisplayDriver_WriteText(struct __ecereNameSpace__ecere__com__Instance * display, struct __ecereNameSpace__ecere__com__Instance * surface, int x, int y, char * text, int len)
{
struct __ecereNameSpace__ecere__gfx__drivers__OGLSurface * oglSurface = ((struct __ecereNameSpace__ecere__gfx__Surface *)(((char *)surface + __ecereClass___ecereNameSpace__ecere__gfx__Surface->offset)))->driverData;
struct __ecereNameSpace__ecere__gfx__drivers__OGLSystem * oglSystem = __extension__ ({
char * __ecTemp1 = (__ecereProp___ecereNameSpace__ecere__gfx__Display_Get_displaySystem(display));

((struct __ecereNameSpace__ecere__gfx__DisplaySystem *)(__ecTemp1 + __ecereClass___ecereNameSpace__ecere__gfx__DisplaySystem->offset));
})->driverData;

oglSystem->loadingFont = 0x1;
if(__ecereProp___ecereNameSpace__ecere__gfx__Surface_Get_textOpacity(surface))
{
int w, h;

((void (*)(struct __ecereNameSpace__ecere__com__Instance *, struct __ecereNameSpace__ecere__gfx__drivers__Font *, char * , int, int * , int * ))__ecereClass___ecereNameSpace__ecere__gfx__drivers__OpenGLDisplayDriver->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__gfx__DisplayDriver_FontExtent])(__ecereProp___ecereNameSpace__ecere__gfx__Display_Get_displaySystem(display), __ecereProp___ecereNameSpace__ecere__gfx__Surface_Get_font(surface), text, len, &w, &h);
((void (*)(struct __ecereNameSpace__ecere__com__Instance *, struct __ecereNameSpace__ecere__com__Instance *, int, int, int, int))__extension__ ({
char *  __ecTemp1 = (__ecereProp___ecereNameSpace__ecere__gfx__Display_Get_displaySystem(display));

((struct __ecereNameSpace__ecere__gfx__DisplaySystem * )(__ecTemp1 + __ecereClass___ecereNameSpace__ecere__gfx__DisplaySystem->offset));
})->driver->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__gfx__DisplayDriver_Area])(display, surface, x, y, x + w - 1, y + h - 1);
}
oglSurface->writingText = 0x1;
glEnable(0x0DE1);
glColor4fv(oglSurface->foreground);
((void (*)(struct __ecereNameSpace__ecere__com__Instance *, struct __ecereNameSpace__ecere__com__Instance *, int, int, char * , int))((struct __ecereNameSpace__ecere__com__Class *)__ecereClass___ecereNameSpace__ecere__gfx__drivers__LFBDisplayDriver)->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__gfx__DisplayDriver_WriteText])(display, surface, x, y, text, len);
oglSurface->writingText = 0x0;
oglSystem->loadingFont = 0x0;
glDisable(0x0DE1);
}
