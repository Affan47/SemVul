fixsqrt32(fixed32 x)
{

    unsigned long r = 0, s, v = (unsigned long)x;

#define STEP(k) s = r + (1 << k * 2); r >>= 1; \
    if (s <= v) { v -= s; r |= (1 << k * 2); }

    STEP(15);
    STEP(14);
    STEP(13);
    STEP(12);
    STEP(11);
    STEP(10);
    STEP(9);
    STEP(8);
    STEP(7);
    STEP(6);
    STEP(5);
    STEP(4);
    STEP(3);
    STEP(2);
    STEP(1);
    STEP(0);

    return (fixed32)(r << (PRECISION / 2));
}
