__ecereNameSpace__ecere__gfx__drivers__BMP888_A(struct __ecereNameSpace__ecere__gfx__drivers__LFBSystem * lfbSystem, struct __ecereNameSpace__ecere__com__Instance * src, struct __ecereNameSpace__ecere__com__Instance * dst)
{
unsigned int c;
unsigned int pixel;

{
unsigned int x, y, ic;

for(y = 0; y < ((struct __ecereNameSpace__ecere__gfx__Bitmap *)(((char *)dst + __ecereClass___ecereNameSpace__ecere__gfx__Bitmap->offset)))->height; y++)
{
c = y * ((struct __ecereNameSpace__ecere__gfx__Bitmap *)(((char *)dst + __ecereClass___ecereNameSpace__ecere__gfx__Bitmap->offset)))->stride;
ic = y * ((struct __ecereNameSpace__ecere__gfx__Bitmap *)(((char *)src + __ecereClass___ecereNameSpace__ecere__gfx__Bitmap->offset)))->stride;
for(x = 0; x < ((struct __ecereNameSpace__ecere__gfx__Bitmap *)(((char *)dst + __ecereClass___ecereNameSpace__ecere__gfx__Bitmap->offset)))->width; x++, c++, ic++)
{
pixel = ((unsigned int *)((struct __ecereNameSpace__ecere__gfx__Bitmap *)(((char *)src + __ecereClass___ecereNameSpace__ecere__gfx__Bitmap->offset)))->picture)[ic];
((struct __ecereNameSpace__ecere__gfx__Bitmap *)(((char *)dst + __ecereClass___ecereNameSpace__ecere__gfx__Bitmap->offset)))->picture[c] = ((unsigned char)((pixel & 0xFF000000) >> 24));
}
}
}
}
