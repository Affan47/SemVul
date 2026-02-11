fuji_rotate_INDI(ushort(**image_p)[4], int *height_p,
                            int *width_p, int *fuji_width_p, const int colors,
                            const double step, void *dcraw)
{
    int height = *height_p, width = *width_p, fuji_width = *fuji_width_p;
    ushort(*image)[4] = *image_p;
    int i, row, col;
    float r, c, fr, fc;
    int ur, uc;
    ushort wide, high, (*img)[4], (*pix)[4];

    if (!fuji_width) return;
    dcraw_message(dcraw, DCRAW_VERBOSE, _("Rotating image 45 degrees...\n"));
    fuji_width = (fuji_width - 1);
    wide = fuji_width / step;
    high = (height - fuji_width) / step;
    img = (ushort(*)[4]) calloc(wide * high, sizeof * img);
    merror(img, "fuji_rotate()");

#ifdef _OPENMP
    #pragma omp parallel for default(shared) private(row,col,ur,uc,r,c,fr,fc,pix,i)
#endif
    for (row = 0; row < high; row++) {
        for (col = 0; col < wide; col++) {
            ur = r = fuji_width + (row - col) * step;
            uc = c = (row + col) * step;
            if (ur > height - 2 || uc > width - 2) continue;
            fr = r - ur;
            fc = c - uc;
            pix = image + ur * width + uc;
            for (i = 0; i < colors; i++)
                img[row * wide + col][i] =
                    (pix[    0][i] * (1 - fc) + pix[      1][i] * fc) * (1 - fr) +
                    (pix[width][i] * (1 - fc) + pix[width + 1][i] * fc) * fr;
        }
    }
    free(image);
    width  = wide;
    height = high;
    image  = img;
    fuji_width = 0;
    *height_p = height;
    *width_p = width;
    *fuji_width_p = fuji_width;
    *image_p = image;
}
