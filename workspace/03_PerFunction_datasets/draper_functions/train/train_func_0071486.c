__ecereMethod___ecereNameSpace__ecere__gfx__bitmaps__PNGFormat_Save(struct __ecereNameSpace__ecere__com__Instance * bitmap, char * filename, void * options)
{
unsigned int result = 0x0;
struct __ecereNameSpace__ecere__com__Instance * tempBitmap = (((void *)0));

if(bitmap && ((struct __ecereNameSpace__ecere__gfx__Bitmap *)(((char *)bitmap + __ecereClass___ecereNameSpace__ecere__gfx__Bitmap->offset)))->pixelFormat != 8)
{
tempBitmap = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass___ecereNameSpace__ecere__gfx__Bitmap);
if(__ecereMethod___ecereNameSpace__ecere__gfx__Bitmap_Copy(tempBitmap, bitmap) && __ecereMethod___ecereNameSpace__ecere__gfx__Bitmap_Convert(tempBitmap, (((void *)0)), 8, (((void *)0))))
bitmap = tempBitmap;
else
bitmap = (((void *)0));
}
if(bitmap)
{
struct __ecereNameSpace__ecere__com__Instance * f = __ecereNameSpace__ecere__sys__FileOpen(filename, 2);

if(f)
{
png_structp png_ptr = png_create_write_struct("1.2.50", (((void *)0)), (((void *)0)), (((void *)0)));

if(png_ptr)
{
png_infop info_ptr = png_create_info_struct(png_ptr);

if(info_ptr)
{
if(!_setjmp((*(png_ptr)).jmpbuf))
{
unsigned int y;

png_set_write_fn(png_ptr, f, __ecereNameSpace__ecere__gfx__bitmaps__WriteData, (((void *)0)));
png_set_IHDR(png_ptr, info_ptr, ((struct __ecereNameSpace__ecere__gfx__Bitmap *)(((char *)bitmap + __ecereClass___ecereNameSpace__ecere__gfx__Bitmap->offset)))->width, ((struct __ecereNameSpace__ecere__gfx__Bitmap *)(((char *)bitmap + __ecereClass___ecereNameSpace__ecere__gfx__Bitmap->offset)))->height, 8, (2 | 4), 0, 0, 0);
png_write_info(png_ptr, info_ptr);
for(y = 0; y < ((struct __ecereNameSpace__ecere__gfx__Bitmap *)(((char *)bitmap + __ecereClass___ecereNameSpace__ecere__gfx__Bitmap->offset)))->height; y++)
{
unsigned char * rowPtr = (unsigned char *)(((unsigned int *)((struct __ecereNameSpace__ecere__gfx__Bitmap *)(((char *)bitmap + __ecereClass___ecereNameSpace__ecere__gfx__Bitmap->offset)))->picture) + y * ((struct __ecereNameSpace__ecere__gfx__Bitmap *)(((char *)bitmap + __ecereClass___ecereNameSpace__ecere__gfx__Bitmap->offset)))->stride);

png_write_rows(png_ptr, &rowPtr, 1);
}
png_write_end(png_ptr, info_ptr);
result = 0x1;
}
}
png_destroy_write_struct(&png_ptr, &info_ptr);
}
(__ecereNameSpace__ecere__com__eInstance_DecRef(f), f = 0);
}
}
if(tempBitmap)
(__ecereNameSpace__ecere__com__eInstance_DecRef(tempBitmap), tempBitmap = 0);
return result;
}
