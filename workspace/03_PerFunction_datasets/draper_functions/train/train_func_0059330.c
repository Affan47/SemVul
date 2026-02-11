colormap_image_ordered(Gif_Image* gfi, uint8_t* all_new_data,
                                   Gif_Colormap* old_cm, kd3_tree* kd3,
                                   uint32_t* histogram,
                                   const uint8_t* matrix) {
    int mw = matrix[0], mh = matrix[1], nplan = matrix[2];
    uint8_t* plan = Gif_NewArray(uint8_t, nplan * old_cm->ncol);
    int i, x, y;


    for (i = 0; i != old_cm->ncol; ++i)
        old_cm->col[i].haspixel = 0;


    ordered_dither_lum = Gif_NewArray(int, kd3->nitems);
    for (i = 0; i != kd3->nitems; ++i)
        ordered_dither_lum[i] = kc_luminance(&kd3->items[i].k);


    if ((mw & (mw - 1)) == 0 && (mh & (mh - 1)) == 0
        && (nplan & (nplan - 1)) == 0)
        pow2_ordered_dither(gfi, all_new_data, old_cm, kd3, histogram,
                            matrix, plan);
    else
        for (y = 0; y != gfi->height; ++y) {
            uint8_t *data, *new_data, *thisplan;
            data = gfi->img[y];
            new_data = all_new_data + y * gfi->width;

            for (x = 0; x != gfi->width; ++x)

                if (data[x] != gfi->transparent) {
                    thisplan = &plan[nplan * data[x]];
                    if (!old_cm->col[data[x]].haspixel)
                        set_ordered_dither_plan(thisplan, nplan, matrix[3],
                                                &old_cm->col[data[x]], kd3);
                    i = matrix[4 + (x + gfi->left) % mw
                               + ((y + gfi->top) % mh) * mw];
                    new_data[x] = thisplan[i];
                    histogram[new_data[x]]++;
                }
        }


    Gif_DeleteArray(ordered_dither_lum);
    Gif_DeleteArray(plan);
}
