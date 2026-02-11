__ecereMethod___ecereNameSpace__ecere__gui__controls__ProgressBar_OnRedraw(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * surface)
{
struct __ecereNameSpace__ecere__gui__controls__ProgressBar * __ecerePointer___ecereNameSpace__ecere__gui__controls__ProgressBar = (struct __ecereNameSpace__ecere__gui__controls__ProgressBar *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__ProgressBar->offset) : 0);

if(__ecerePointer___ecereNameSpace__ecere__gui__controls__ProgressBar->range)
{
struct __ecereNameSpace__ecere__sys__Size __simpleStruct3;
struct __ecereNameSpace__ecere__sys__Size __simpleStruct2;
struct __ecereNameSpace__ecere__sys__Size __simpleStruct1;
int __simpleStruct0;
int pos = (int)((float)(float)(int)(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_clientSize(this, &__simpleStruct1), __simpleStruct1).w * (float)__ecerePointer___ecereNameSpace__ecere__gui__controls__ProgressBar->position / (float)__ecerePointer___ecereNameSpace__ecere__gui__controls__ProgressBar->range);
int w, h;
char text[10];

__ecereMethod___ecereNameSpace__ecere__gfx__Surface_SetBackground(surface, __ecereProp___ecereNameSpace__ecere__gfx__ColorAlpha_Set___ecereNameSpace__ecere__gfx__Color(0xAA));
__ecereMethod___ecereNameSpace__ecere__gfx__Surface_Area(surface, 0, 0, pos, (int)((__ecereProp___ecereNameSpace__ecere__gui__Window_Get_clientSize(this, &__simpleStruct2), __simpleStruct2.h - 1)));
__ecereMethod___ecereNameSpace__ecere__gfx__Surface_SetForeground(surface, __ecereProp___ecereNameSpace__ecere__gfx__ColorAlpha_Set___ecereNameSpace__ecere__gfx__Color(0xFFFFFF));
sprintf(text, "%d%%", (int)((float)__ecerePointer___ecereNameSpace__ecere__gui__controls__ProgressBar->position * 100.0f / (float)__ecerePointer___ecereNameSpace__ecere__gui__controls__ProgressBar->range));
__ecereMethod___ecereNameSpace__ecere__gfx__Surface_TextExtent(surface, text, strlen(text), &w, &h);
__ecereMethod___ecereNameSpace__ecere__gfx__Surface_WriteText(surface, (__simpleStruct0 = pos - w, (__simpleStruct0 > 0) ? __simpleStruct0 : 0), (int)(((__ecereProp___ecereNameSpace__ecere__gui__Window_Get_clientSize(this, &__simpleStruct3), __simpleStruct3.h - h)) / 2), text, strlen(text));
}
}
