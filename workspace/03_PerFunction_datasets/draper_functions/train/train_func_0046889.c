__ecereMethod___ecereNameSpace__ecere__gfx__drivers__XDisplayDriver_Rectangle(struct __ecereNameSpace__ecere__com__Instance * display, struct __ecereNameSpace__ecere__com__Instance * surface, int x1, int y1, int x2, int y2)
{
struct __ecereNameSpace__ecere__gfx__drivers__XDisplay * xDisplay = ((struct __ecereNameSpace__ecere__gfx__Display *)(((char *)display + __ecereClass___ecereNameSpace__ecere__gfx__Display->offset)))->driverData;
struct __ecereNameSpace__ecere__gfx__drivers__XSurface * xSurface = ((struct __ecereNameSpace__ecere__gfx__Surface *)(((char *)surface + __ecereClass___ecereNameSpace__ecere__gfx__Surface->offset)))->driverData;

if(((unsigned char)((xSurface->foreground & 0xFF000000) >> 24)) < (unsigned char)255)
{
((void (*)(struct __ecereNameSpace__ecere__com__Instance *, struct __ecereNameSpace__ecere__com__Instance *, int, int, int, int))__ecereClass___ecereNameSpace__ecere__gfx__drivers__XDisplayDriver->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__gfx__DisplayDriver_DrawLine])(display, surface, x1, y1, x2 - 1, y1);
((void (*)(struct __ecereNameSpace__ecere__com__Instance *, struct __ecereNameSpace__ecere__com__Instance *, int, int, int, int))__ecereClass___ecereNameSpace__ecere__gfx__drivers__XDisplayDriver->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__gfx__DisplayDriver_DrawLine])(display, surface, x2, y1, x2, y2 - 1);
((void (*)(struct __ecereNameSpace__ecere__com__Instance *, struct __ecereNameSpace__ecere__com__Instance *, int, int, int, int))__ecereClass___ecereNameSpace__ecere__gfx__drivers__XDisplayDriver->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__gfx__DisplayDriver_DrawLine])(display, surface, x1, y2, x2 - 1, y2);
((void (*)(struct __ecereNameSpace__ecere__com__Instance *, struct __ecereNameSpace__ecere__com__Instance *, int, int, int, int))__ecereClass___ecereNameSpace__ecere__gfx__drivers__XDisplayDriver->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__gfx__DisplayDriver_DrawLine])(display, surface, x1, y1 + 1, x1, y2 - 1);
}
else
XDrawRectangle(__ecereNameSpace__ecere__gui__drivers__xGlobalDisplay, xDisplay->pixmap, xDisplay->gc, x1 + ((struct __ecereNameSpace__ecere__gfx__Surface *)(((char *)surface + __ecereClass___ecereNameSpace__ecere__gfx__Surface->offset)))->offset.x, y1 + ((struct __ecereNameSpace__ecere__gfx__Surface *)(((char *)surface + __ecereClass___ecereNameSpace__ecere__gfx__Surface->offset)))->offset.y, x2 - x1, y2 - y1);
}
