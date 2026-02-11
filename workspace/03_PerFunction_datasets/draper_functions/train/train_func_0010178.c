__ecereInstMeth___ecereNameSpace__ecere__gui__controls__EditBox_NotifyModified__00000015(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * control)
{
struct __ecereNameSpace__ecere__gfx__ColorHSV __simpleStruct4;
struct __ecereNameSpace__ecere__gfx__ColorCMYK __simpleStruct3;
struct __ecereNameSpace__ecere__gfx__ColorLab __simpleStruct2;
struct __ecereNameSpace__ecere__gfx__ColorRGB __simpleStruct1;
int __simpleStruct0;
struct __ecereNameSpace__ecere__gui__dialogs__ColorPicker * __ecerePointer___ecereNameSpace__ecere__gui__dialogs__ColorPicker = (struct __ecereNameSpace__ecere__gui__dialogs__ColorPicker *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__dialogs__ColorPicker->offset) : 0);
struct __ecereNameSpace__ecere__gfx__ColorRGB rgb;
int value = strtol(__ecereProp___ecereNameSpace__ecere__gui__controls__EditBox_Get_contents(control), (((void *)0)), 10);

value = (__simpleStruct0 = ((value > 0) ? value : 0), (__simpleStruct0 < 255) ? __simpleStruct0 : 255);
__ecerePointer___ecereNameSpace__ecere__gui__dialogs__ColorPicker->argb = (__ecerePointer___ecereNameSpace__ecere__gui__dialogs__ColorPicker->argb & ~0xFFFFFF) | (((unsigned int)(((unsigned int)((__ecerePointer___ecereNameSpace__ecere__gui__dialogs__ColorPicker->argb & 0xFFFFFF) >> 0)) & ~0xFF0000) | (((unsigned int)(unsigned char)value) << 16)) << 0);
rgb = (__ecereProp___ecereNameSpace__ecere__gfx__Color_Get___ecereNameSpace__ecere__gfx__ColorRGB(__ecereProp___ecereNameSpace__ecere__gfx__ColorAlpha_Get___ecereNameSpace__ecere__gfx__Color(__ecerePointer___ecereNameSpace__ecere__gui__dialogs__ColorPicker->argb), &__simpleStruct1), __simpleStruct1);
__ecerePointer___ecereNameSpace__ecere__gui__dialogs__ColorPicker->Lab = (__ecereProp___ecereNameSpace__ecere__gfx__ColorLab_Set___ecereNameSpace__ecere__gfx__ColorRGB(&__simpleStruct2, &rgb), __simpleStruct2);
__ecerePointer___ecereNameSpace__ecere__gui__dialogs__ColorPicker->cmyk = (__ecereProp___ecereNameSpace__ecere__gfx__ColorCMYK_Set___ecereNameSpace__ecere__gfx__ColorRGB(&__simpleStruct3, &rgb), __simpleStruct3);
__ecerePointer___ecereNameSpace__ecere__gui__dialogs__ColorPicker->hsv = (__ecereProp___ecereNameSpace__ecere__gfx__ColorHSV_Set___ecereNameSpace__ecere__gfx__ColorRGB(&__simpleStruct4, &rgb), __simpleStruct4);
__ecereMethod___ecereNameSpace__ecere__gui__dialogs__ColorPicker_UpdatePosition(this);
return 0x1;
}
