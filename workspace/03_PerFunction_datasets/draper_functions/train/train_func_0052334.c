__ecereNameSpace__ecere__gfx__drivers__BLIT_WTF(struct __ecereNameSpace__ecere__com__Instance * src, struct __ecereNameSpace__ecere__com__Instance * dst, int dx, int dy, int sx, int sy, int w, int h)
{
int y;
unsigned int adddest = ((struct __ecereNameSpace__ecere__gfx__Bitmap *)(((char *)dst + __ecereClass___ecereNameSpace__ecere__gfx__Bitmap->offset)))->stride, addsource = ((struct __ecereNameSpace__ecere__gfx__Bitmap *)(((char *)src + __ecereClass___ecereNameSpace__ecere__gfx__Bitmap->offset)))->stride;
unsigned short * source = (unsigned short *)((struct __ecereNameSpace__ecere__gfx__Bitmap *)(((char *)src + __ecereClass___ecereNameSpace__ecere__gfx__Bitmap->offset)))->picture + sy * addsource + sx;
unsigned short * dest = (unsigned short *)((struct __ecereNameSpace__ecere__gfx__Bitmap *)(((char *)dst + __ecereClass___ecereNameSpace__ecere__gfx__Bitmap->offset)))->picture + dy * adddest + dx;
int x;

dest += w - 1;
adddest += w;
addsource -= w;
for(y = 0; y < h; y++)
{
for(x = 0; x < w; x++)
{
if(*source)
*dest = (*source);
source++;
dest--;
}
;
source += addsource;
dest += adddest;
}
}
