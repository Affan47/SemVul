G_FROMYUV(unsigned char y, unsigned char u, unsigned char v)
{
return CLIP((y) + LutGu[(u)] + LutGv[(v)]);
}
