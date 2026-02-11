__ecereNameSpace__ecere__gfx__drivers__STRETCH_W(struct __ecereNameSpace__ecere__com__Instance * src, struct __ecereNameSpace__ecere__com__Instance * dst, int dx, int dy, int sx, int sy, int w, int h, int sw, int sh)
{
int x, y;
unsigned int xerr, yerr;
unsigned int adddest = ((struct __ecereNameSpace__ecere__gfx__Bitmap *)(((char *)dst + __ecereClass___ecereNameSpace__ecere__gfx__Bitmap->offset)))->stride, addsource = ((struct __ecereNameSpace__ecere__gfx__Bitmap *)(((char *)src + __ecereClass___ecereNameSpace__ecere__gfx__Bitmap->offset)))->stride;
unsigned short * backsrc;
unsigned short * source = ((unsigned short *)((struct __ecereNameSpace__ecere__gfx__Bitmap *)(((char *)src + __ecereClass___ecereNameSpace__ecere__gfx__Bitmap->offset)))->picture) + sy * addsource + sx;
unsigned short * dest = ((unsigned short *)((struct __ecereNameSpace__ecere__gfx__Bitmap *)(((char *)dst + __ecereClass___ecereNameSpace__ecere__gfx__Bitmap->offset)))->picture) + dy * adddest + dx;

;
if(1 < 0)
source += sw - 1;
adddest -= w;
yerr = 0;
for(y = 0; y < sh; y++)
{
yerr += h;
backsrc = source;
while(yerr >= sh)
{
yerr -= sh;
xerr = 0;
for(x = 0; x < sw; x++)
{
xerr += w;
while(xerr >= sw)
{
xerr -= sw;
*dest = (*source);
dest++;
}
source += 1;
}
dest += adddest;
source = backsrc;
}
source += addsource;
}
}
