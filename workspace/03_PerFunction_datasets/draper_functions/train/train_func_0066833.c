rotateAMGrayCornerLow(l_uint32  *datad,
                      l_int32    w,
                      l_int32    h,
                      l_int32    wpld,
                      l_uint32  *datas,
                      l_int32    wpls,
                      l_float32  angle,
                      l_uint8    grayval)
{
l_int32    i, j, wm2, hm2;
l_int32    xpm, ypm, xp, yp, xf, yf;
l_int32    v00, v01, v10, v11;
l_uint8    val;
l_uint32  *lines, *lined;
l_float32  sina, cosa;

    wm2 = w - 2;
    hm2 = h - 2;
    sina = 16. * sin(angle);
    cosa = 16. * cos(angle);

    for (i = 0; i < h; i++) {
        lined = datad + i * wpld;
        for (j = 0; j < w; j++) {
            xpm = (l_int32)(j * cosa + i * sina);
            ypm = (l_int32)(i * cosa - j * sina);
            xp = xpm >> 4;
            yp = ypm >> 4;
            xf = xpm & 0x0f;
            yf = ypm & 0x0f;


            if (xp < 0 || yp < 0 || xp > wm2 || yp > hm2) {
                SET_DATA_BYTE(lined, j, grayval);
                continue;
            }

            lines = datas + yp * wpls;


            v00 = (16 - xf) * (16 - yf) * GET_DATA_BYTE(lines, xp);
            v10 = xf * (16 - yf) * GET_DATA_BYTE(lines, xp + 1);
            v01 = (16 - xf) * yf * GET_DATA_BYTE(lines + wpls, xp);
            v11 = xf * yf * GET_DATA_BYTE(lines + wpls, xp + 1);
            val = (l_uint8)((v00 + v01 + v10 + v11 + 128) / 256);
            SET_DATA_BYTE(lined, j, val);
        }
    }

    return;
}
