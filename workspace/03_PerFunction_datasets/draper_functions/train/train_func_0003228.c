inplace_divrem1(digit *pout, digit *pin, Py_ssize_t size, digit n)
{
    twodigits rem = 0;

    assert(n > 0 && n <= PyLong_MASK);
    pin += size;
    pout += size;
    while (--size >= 0) {
        digit hi;
        rem = (rem << PyLong_SHIFT) | *--pin;
        *--pout = hi = (digit)(rem / n);
        rem -= (twodigits)hi * n;
    }
    return (digit)rem;
}
