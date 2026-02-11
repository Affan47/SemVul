DrawLineMarginIcon(struct __ecereNameSpace__ecere__com__Instance * surface, struct __ecereNameSpace__ecere__com__Instance * resource, int line, int lineH, int scrollY, int boxH)
{
int lineY;

if(line)
{
lineY = (line - 1) * lineH;
if(lineY + lineH > scrollY && lineY + lineH < scrollY + boxH)
{
struct __ecereNameSpace__ecere__com__Instance * bitmap = __ecereProp___ecereNameSpace__ecere__gfx__BitmapResource_Get_bitmap(resource);

if(bitmap)
__ecereMethod___ecereNameSpace__ecere__gfx__Surface_Blit(surface, bitmap, 0, lineY - scrollY + (lineH - ((struct __ecereNameSpace__ecere__gfx__Bitmap *)(((char *)bitmap + __ecereClass___ecereNameSpace__ecere__gfx__Bitmap->offset)))->height) / 2 + 1, 0, 0, ((struct __ecereNameSpace__ecere__gfx__Bitmap *)(((char *)bitmap + __ecereClass___ecereNameSpace__ecere__gfx__Bitmap->offset)))->width, ((struct __ecereNameSpace__ecere__gfx__Bitmap *)(((char *)bitmap + __ecereClass___ecereNameSpace__ecere__gfx__Bitmap->offset)))->height);
}
}
}
