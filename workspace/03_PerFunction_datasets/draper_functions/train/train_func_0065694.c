ImageOilPaint (gpaint_image * input, gpaint_image * output)
{
    unsigned char *op = image_pixels (output);
    int x, y, xx, yy, i;
    int rVal, gVal, bVal;
    int rCnt, gCnt, bCnt;
    int rHist[256], gHist[256], bHist[256];
    int oilArea_2;
    int width = image_width (input);
    int height = image_height (input);


    oilArea_2 = ImgProcessInfo.oilArea / 2;

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {


            rCnt = gCnt = bCnt = 0;
            rVal = gVal = bVal = 0;
            for (i = 0; i < sizeof (rHist) / sizeof (int); i++)
                rHist[i] = gHist[i] = bHist[i] = 0;

            for (yy = y - oilArea_2; yy < y + oilArea_2; yy++)
            {
                if (yy < 0 || yy >= height)
                    continue;
                for (xx = x - oilArea_2; xx < x + oilArea_2; xx++)
                {
                    int c, p;
                    unsigned char *rgb;

                    if (xx < 0 || xx >= width)
                        continue;

                    rgb = ImagePixel (input, xx, yy);

                    if ((c = ++rHist[(p = rgb[0]) / 4]) > rCnt)
                    {
                        rVal = p;
                        rCnt = c;
                    }
                    if ((c = ++gHist[(p = rgb[1]) / 4]) > gCnt)
                    {
                        gVal = p;
                        gCnt = c;
                    }
                    if ((c = ++bHist[(p = rgb[2]) / 4]) > bCnt)
                    {
                        bVal = p;
                        bCnt = c;
                    }
                }
            }

            *op++ = rVal;
            *op++ = gVal;
            *op++ = bVal;
            op += image_pixelsize (output) - 3;
        }

        if (y % 16 == 0)
            StateTimeStep ();
        op += image_rowstride (output) - width * image_pixelsize (output);
    }


}
