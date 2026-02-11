deblock_v_consider_entire(guchar *blocks, guint stride)
{
    gint count, i, j;
    guchar *p1, *p2;

    count = 0;

    p1 = blocks + stride;
    p2 = blocks + (stride * 2);

    for (i = 0; i < 7; i++) {

        for (j = 0; j < 8; j++) {
            gint v1, v2, v;

            v1 = p1[j];
            v2 = p2[j];

            v = v1 - v2;
            if (v <= 0)
                v = v2 - v1;

            if (v <= 1)
                count++;
        }

        p1 += stride;
        p2 += stride;
    }

    return (count > 40);
}
