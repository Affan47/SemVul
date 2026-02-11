rgbshift (unsigned char *rgb)
{
    zcolor_Bright[0] = (rgb[0] + 0x30) < 0xff ? (rgb[0] + 0x30) : 0xff;
    zcolor_Bright[1] = (rgb[1] + 0x30) < 0xff ? (rgb[1] + 0x30) : 0xff;
    zcolor_Bright[2] = (rgb[2] + 0x30) < 0xff ? (rgb[2] + 0x30) : 0xff;

    return zcolor_Bright;
}
