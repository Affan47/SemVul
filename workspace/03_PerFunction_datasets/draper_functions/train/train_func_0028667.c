DrawStipple(struct __ecereNameSpace__ecere__com__Instance * surface, struct __ecereNameSpace__ecere__sys__Size * clientSize)
{
int x1 = 0;
int y1 = 0;
int x2 = (int)(clientSize->w - 1);
int y2 = (int)(clientSize->h - 1);

if((x2 - x1) & 1)
x2--;
if((y2 - y1) & 1)
y2--;
__ecereMethod___ecereNameSpace__ecere__gfx__Surface_LineStipple(surface, 0x5555);
__ecereMethod___ecereNameSpace__ecere__gfx__Surface_Rectangle(surface, x1, y1, x2, y2);
__ecereMethod___ecereNameSpace__ecere__gfx__Surface_LineStipple(surface, 0);
}
