CreateQuantPixels(TreeNode tree,
        Pointer input, unsigned char *output, int knt, int float_pixels)
{
    int i;
    unsigned char *s = (unsigned char *)input;
    unsigned char *d = output;
    int skipsize;
    struct color pbuf;

    skipsize = float_pixels ? 3*sizeof(float) : sizeof(struct color);

    for (i = 0; i < knt; i++, s += skipsize, d++)
    {
        int q;

        if (i == find_me)
            found();

            if (float_pixels)
            {
                float fr = ((float *)s)[0];
                float fg = ((float *)s)[1];
                float fb = ((float *)s)[2];
                pbuf.r = fr >= 1.0 ? 255 : fr <= 0.0 ? 0 :
                                        (unsigned char)(255 * fr);
                pbuf.g = fg >= 1.0 ? 255 : fg <= 0.0 ? 0 :
                                        (unsigned char)(255 * fg);
                pbuf.b = fb >= 1.0 ? 255 : fb <= 0.0 ? 0 :
                                        (unsigned char)(255 * fb);

                q = SearchTree(tree, (Color)&pbuf, 0);
            }
            else
                q = SearchTree(tree, (Color)s, 0);

        if (q < 0)
            return ERROR;

        *d = q;
    }

    return 1;
}
