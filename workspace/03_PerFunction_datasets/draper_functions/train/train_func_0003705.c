generate_grey_image(uint16 *buf, uint16 width, uint16 height)
{
    uint8 lum = 0xFF;
    int i,j;
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            *(buf + width * i + j) = lum<<8;
        }
        lum -= 0x01;
    }
}
