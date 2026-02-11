__ecereMethod___ecereNameSpace__ecere__gfx__drivers__LFBDisplayDriver_SetBackground(struct __ecereNameSpace__ecere__com__Instance * display, struct __ecereNameSpace__ecere__com__Instance * surface, unsigned int color)
{
struct __ecereNameSpace__ecere__gfx__drivers__LFBDisplay * lfbDisplay = display ? ((struct __ecereNameSpace__ecere__gfx__Display *)(((char *)display + __ecereClass___ecereNameSpace__ecere__gfx__Display->offset)))->driverData : (((void *)0));
struct __ecereNameSpace__ecere__gfx__drivers__LFBSurface * lfbSurface = ((struct __ecereNameSpace__ecere__gfx__Surface *)(((char *)surface + __ecereClass___ecereNameSpace__ecere__gfx__Surface->offset)))->driverData;

color = color;
switch(((struct __ecereNameSpace__ecere__gfx__Bitmap *)(((char *)lfbSurface->bitmap + __ecereClass___ecereNameSpace__ecere__gfx__Bitmap->offset)))->pixelFormat)
{
case 1:
if(display)
lfbSurface->background = lfbDisplay->rgbLookup[(unsigned short)(unsigned short)__ecereProp___ecereNameSpace__ecere__gfx__Color555_Set___ecereNameSpace__ecere__gfx__Color(__ecereProp___ecereNameSpace__ecere__gfx__ColorAlpha_Get___ecereNameSpace__ecere__gfx__Color(color))];
else
lfbSurface->background = __ecereNameSpace__ecere__gfx__BestColorMatch(((struct __ecereNameSpace__ecere__gfx__Bitmap *)(((char *)lfbSurface->bitmap + __ecereClass___ecereNameSpace__ecere__gfx__Bitmap->offset)))->palette, 0, 255, __ecereProp___ecereNameSpace__ecere__gfx__ColorAlpha_Get___ecereNameSpace__ecere__gfx__Color(color));
break;
case 2:
lfbSurface->background = (unsigned short)(unsigned short)__ecereProp___ecereNameSpace__ecere__gfx__Color444_Set___ecereNameSpace__ecere__gfx__Color(__ecereProp___ecereNameSpace__ecere__gfx__ColorAlpha_Get___ecereNameSpace__ecere__gfx__Color(color));
break;
case 3:
lfbSurface->background = (unsigned short)(unsigned short)__ecereProp___ecereNameSpace__ecere__gfx__Color555_Set___ecereNameSpace__ecere__gfx__Color(__ecereProp___ecereNameSpace__ecere__gfx__ColorAlpha_Get___ecereNameSpace__ecere__gfx__Color(color));
break;
case 4:
lfbSurface->background = (unsigned short)(unsigned short)__ecereProp___ecereNameSpace__ecere__gfx__Color565_Set___ecereNameSpace__ecere__gfx__Color(__ecereProp___ecereNameSpace__ecere__gfx__ColorAlpha_Get___ecereNameSpace__ecere__gfx__Color(color));
break;
case 5:
lfbSurface->background = (unsigned int)color;
break;
case 8:
lfbSurface->background = (unsigned int)(unsigned int)__ecereProp___ecereNameSpace__ecere__gfx__ColorRGBA_Set___ecereNameSpace__ecere__gfx__ColorAlpha(color);
break;
case 7:
if(display)
lfbSurface->background = __ecereNameSpace__ecere__gfx__BestColorMatch(((struct __ecereNameSpace__ecere__gfx__Bitmap *)(((char *)lfbDisplay->bitmap + __ecereClass___ecereNameSpace__ecere__gfx__Bitmap->offset)))->palette, 0, 15, __ecereProp___ecereNameSpace__ecere__gfx__ColorAlpha_Get___ecereNameSpace__ecere__gfx__Color(color)) << 12;
else
lfbSurface->background = __ecereNameSpace__ecere__gfx__BestColorMatch(((struct __ecereNameSpace__ecere__gfx__Bitmap *)(((char *)lfbSurface->bitmap + __ecereClass___ecereNameSpace__ecere__gfx__Bitmap->offset)))->palette, 0, 15, __ecereProp___ecereNameSpace__ecere__gfx__ColorAlpha_Get___ecereNameSpace__ecere__gfx__Color(color)) << 12;
break;
}
}
