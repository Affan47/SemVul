__ecereNameSpace__ecere__gfx__drivers__hb_canRender(HB_Font font, unsigned short * string, unsigned int length)
{
FT_Face face = ((struct __ecereNameSpace__ecere__gfx__drivers__FontEntry *)(*font).userData)->face;
int c, nw;

for(c = 0; c < length; c += nw)
{
unsigned int ch = __ecereNameSpace__ecere__gfx__drivers__UTF16GetChar(string + c, &nw);

if(!FT_Get_Char_Index(face, ch))
return (unsigned char)0;
}
return (unsigned char)1;
}
