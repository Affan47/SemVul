util_lcm(int64_t x, int64_t y)
{


    int64_t x1 = x;
    int64_t y1 = y;

    int p2 = 0;
    while ((x1 & 1) == 0 && (y1 & 1) == 0) {
        ++p2;
        x1 >>= 1;
        y1 >>= 1;
    }

    int64_t t;
    if ((x1 & 1) == 1) {
        t = -y1;
    } else {
        t = x1;
    }

    while (t != 0) {
        while ((t & 1) == 0) {
            t = t >> 1;
        }
        if (t > 0) {
            x1 = t;
        } else {
            y1 = -t;
        }
        t = x1 - y1;
    }

    int64_t gcd = x1 << p2;


    return x / gcd * y;
}
