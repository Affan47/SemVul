cdiv (complex a,complex b)
{
    double ratio, den;
    complex c;

    if (fabs(b.re) <= fabs(b.im)) {
        ratio = b.re / b.im;
        den = b.im * (1 + ratio * ratio);
        c.re = (a.re * ratio + a.im) / den;
        c.im = (a.im * ratio - a.re) / den;
    }
    else {
        ratio = b.im / b.re;
        den = b.re * (1 + ratio * ratio);
        c.re = (a.re + a.im * ratio) / den;
        c.im = (a.im - a.re * ratio) / den;
    }
    return(c);
}
