__ecereMethod___ecereNameSpace__ecere__gfx__drivers__XDisplayDriver_Clip(struct __ecereNameSpace__ecere__com__Instance * display, struct __ecereNameSpace__ecere__com__Instance * surface, struct __ecereNameSpace__ecere__sys__Box * clip)
{
struct __ecereNameSpace__ecere__gfx__drivers__XSurface * xSurface = ((struct __ecereNameSpace__ecere__gfx__Surface *)(((char *)surface + __ecereClass___ecereNameSpace__ecere__gfx__Surface->offset)))->driverData;
struct __ecereNameSpace__ecere__gfx__drivers__XDisplay * xDisplay = ((struct __ecereNameSpace__ecere__gfx__Display *)(((char *)display + __ecereClass___ecereNameSpace__ecere__gfx__Display->offset)))->driverData;
unsigned int changed = 0x0;
XRectangle rectangle;

if(clip != (((void *)0)))
{
struct __ecereNameSpace__ecere__sys__Box box = *clip;

__ecereMethod___ecereNameSpace__ecere__sys__Box_Clip(&box, &((struct __ecereNameSpace__ecere__gfx__Surface *)(((char *)surface + __ecereClass___ecereNameSpace__ecere__gfx__Surface->offset)))->unclippedBox);
((struct __ecereNameSpace__ecere__gfx__Surface *)(((char *)surface + __ecereClass___ecereNameSpace__ecere__gfx__Surface->offset)))->box = box;
xSurface->clipped = 0x1;
changed = 0x1;
}
else if(xSurface->clipped)
{
((struct __ecereNameSpace__ecere__gfx__Surface *)(((char *)surface + __ecereClass___ecereNameSpace__ecere__gfx__Surface->offset)))->box = ((struct __ecereNameSpace__ecere__gfx__Surface *)(((char *)surface + __ecereClass___ecereNameSpace__ecere__gfx__Surface->offset)))->unclippedBox;
xSurface->clipped = 0x0;
changed = 0x1;
}
if(changed)
{
XRectangle rectangle =
{
(short)(((struct __ecereNameSpace__ecere__gfx__Surface *)(((char *)surface + __ecereClass___ecereNameSpace__ecere__gfx__Surface->offset)))->box.left + ((struct __ecereNameSpace__ecere__gfx__Surface *)(((char *)surface + __ecereClass___ecereNameSpace__ecere__gfx__Surface->offset)))->offset.x), (short)(((struct __ecereNameSpace__ecere__gfx__Surface *)(((char *)surface + __ecereClass___ecereNameSpace__ecere__gfx__Surface->offset)))->box.top + ((struct __ecereNameSpace__ecere__gfx__Surface *)(((char *)surface + __ecereClass___ecereNameSpace__ecere__gfx__Surface->offset)))->offset.y), (short)(((struct __ecereNameSpace__ecere__gfx__Surface *)(((char *)surface + __ecereClass___ecereNameSpace__ecere__gfx__Surface->offset)))->box.right - ((struct __ecereNameSpace__ecere__gfx__Surface *)(((char *)surface + __ecereClass___ecereNameSpace__ecere__gfx__Surface->offset)))->box.left + 1), (short)(((struct __ecereNameSpace__ecere__gfx__Surface *)(((char *)surface + __ecereClass___ecereNameSpace__ecere__gfx__Surface->offset)))->box.bottom - ((struct __ecereNameSpace__ecere__gfx__Surface *)(((char *)surface + __ecereClass___ecereNameSpace__ecere__gfx__Surface->offset)))->box.top + 1)
};

XSetClipRectangles(__ecereNameSpace__ecere__gui__drivers__xGlobalDisplay, xDisplay->gc, 0, 0, &rectangle, 1, 3);
}
}
