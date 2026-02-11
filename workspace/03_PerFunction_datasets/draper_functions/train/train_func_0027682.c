cmyk_to_rgb(byte cmyk[], byte rgb[])
{


    rgb[0] = 255 - min(cmyk[0] + cmyk[3],255);
    rgb[1] = 255 - min(cmyk[1] + cmyk[3],255);
    rgb[2] = 255 - min(cmyk[2] + cmyk[3],255);

}
