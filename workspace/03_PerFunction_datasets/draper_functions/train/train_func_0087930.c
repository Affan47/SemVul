grow21_line(uint8_t *dst, const uint8_t *src,
                        int width)
{
    int w;
    const uint8_t *s1;
    uint8_t *d;

    s1 = src;
    d = dst;
    for(w = width;w >= 4; w-=4) {
        d[1] = d[0] = s1[0];
        d[3] = d[2] = s1[1];
        s1 += 2;
        d += 4;
    }
    for(;w >= 2; w -= 2) {
        d[1] = d[0] = s1[0];
        s1 ++;
        d += 2;
    }


    if (w) {
        d[0] = s1[0];
    }
}
