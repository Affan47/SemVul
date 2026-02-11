__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_FlushBuffer(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * surface, struct __ecereNameSpace__ecere__gui__controls__EditLine * line, int wc, int * renderStart, int * x, int y, int numSpaces, unsigned int drawSpaces, struct __ecereNameSpace__ecere__sys__Box * box)
{
struct __ecereNameSpace__ecere__gui__controls__EditBox * __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox = (struct __ecereNameSpace__ecere__gui__controls__EditBox *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__EditBox->offset) : 0);
int count = wc - *renderStart;

if(count)
{
if(y + (int)__ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->space.h >= box->top && y <= box->bottom)
{
int w;

if(!numSpaces)
{
__ecereMethod___ecereNameSpace__ecere__gfx__Surface_TextFont(surface, __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->font);
__ecereMethod___ecereNameSpace__ecere__gfx__Surface_TextExtent(surface, line->buffer + *renderStart, count, &w, (((void *)0)));
if(*x + w + (3 + (0)) > 0)
__ecereMethod___ecereNameSpace__ecere__gfx__Surface_WriteText(surface, (3 + (0)) + *x, y, line->buffer + *renderStart, count);
*x += w;
}
else
{
w = numSpaces;
if(*x + w + (3 + (0)) > 0 && (drawSpaces || __ecereMethod___ecereNameSpace__ecere__gfx__Surface_GetTextOpacity(surface)))
__ecereMethod___ecereNameSpace__ecere__gfx__Surface_Area(surface, (3 + (0)) + *x - 1, y, (3 + (0)) + *x + w, y + (int)__ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->space.h - 1);
*x += w;
}
}
*renderStart = wc;
}
}
