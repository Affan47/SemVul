__ecereMethod___ecereNameSpace__ecere__gui__controls__ListBox_OnLoadGraphics(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__ecere__gui__controls__ListBox * __ecerePointer___ecereNameSpace__ecere__gui__controls__ListBox = (struct __ecereNameSpace__ecere__gui__controls__ListBox *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__ListBox->offset) : 0);

__ecereMethod___ecereNameSpace__ecere__gfx__Display_FontExtent(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_display(this), __ecereProp___ecereNameSpace__ecere__gui__Window_Get_fontObject(this), "W", 1, (((void *)0)), &__ecerePointer___ecereNameSpace__ecere__gui__controls__ListBox->fontH);
if(!((unsigned int)((__ecerePointer___ecereNameSpace__ecere__gui__controls__ListBox->style & 0x4000) >> 14)))
{
int __simpleStruct0;

__ecerePointer___ecereNameSpace__ecere__gui__controls__ListBox->rowHeight = (__simpleStruct0 = __ecerePointer___ecereNameSpace__ecere__gui__controls__ListBox->fontH + 2, (__simpleStruct0 > 16) ? __simpleStruct0 : 16) + (((unsigned int)((__ecerePointer___ecereNameSpace__ecere__gui__controls__ListBox->style & 0x400) >> 10)) ? 1 : 0);
__ecereMethod___ecereNameSpace__ecere__gui__Window_SetScrollLineStep(this, 8, __ecerePointer___ecereNameSpace__ecere__gui__controls__ListBox->rowHeight);
}
return 0x1;
}
