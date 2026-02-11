__ecereMethod___ecereNameSpace__ecere__gfx__Surface_WriteTextf(struct __ecereNameSpace__ecere__com__Instance * this, int x, int y, char * format, ...)
{
struct __ecereNameSpace__ecere__gfx__Surface * __ecerePointer___ecereNameSpace__ecere__gfx__Surface = (struct __ecereNameSpace__ecere__gfx__Surface *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gfx__Surface->offset) : 0);

if(format)
{
char text[1025];
va_list args;

__builtin_va_start(args, format);
vsnprintf(text, sizeof text, format, args);
text[sizeof text - 1] = (char)0;
((void (*)(struct __ecereNameSpace__ecere__com__Instance *, struct __ecereNameSpace__ecere__com__Instance *, int, int, char * , int))__ecerePointer___ecereNameSpace__ecere__gfx__Surface->driver->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__gfx__DisplayDriver_WriteText])(__ecerePointer___ecereNameSpace__ecere__gfx__Surface->display, this, x, y, text, strlen(text));
__builtin_va_end(args);
}
}
